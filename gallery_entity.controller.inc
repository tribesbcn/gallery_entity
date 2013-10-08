<?php

class GalleryEntityController extends EntityAPIController {

  public function create(array $values = array()) {
    global $user;
    $values += array(
      'name' => '',
      'created' => REQUEST_TIME,
      'changed' => REQUEST_TIME,
      'uid' => $user->uid,
      'status' => 1,
      'restricted_access' => 0,
    );
    return parent::create($values);
  }

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('gallery_entity', $entity);
    
    //$content['author'] = array('#markup' => t('Created by: !author', array('!author' => $wrapper->uid->name->value(array('sanitize' => TRUE)))));
    //$content['name'] = array('#markup' => $entity->name);
    
    /*
    // Make Description and Status themed like default fields.
    $content['description'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' =>t('Description'),
      '#access' => TRUE,
      '#label_display' => 'above',
      '#view_mode' => 'full',
      '#language' => LANGUAGE_NONE,
      '#field_name' => 'field_fake_description',
      '#field_type' => 'text',
      '#entity_type' => 'gallery_entity',
      '#bundle' => $entity->type,
      '#items' => array(array('value' => $entity->description)),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->description))
    );
    */

    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }
  
  /**
   * Scan a folder and creates taxonomy terms for gallery categorization.
   * Creates the gallery entities and import the images to each gallery.
   */
  public function scan_folder($path, $vid, &$parents_ids=array(), &$function_resp=array(), $level=0, $gallery_id=0){
  	//$folder = $_SERVER['DOCUMENT_ROOT']."/FTP_ITEMS/";
  	$ftp_folder = scandir($path);
  	foreach($ftp_folder as $folder_item){
  		if($folder_item != "." && $folder_item != ".."){
  			$new_path = $path.$folder_item;
  			$first_slash_pos = strpos($folder_item, "_");
  			//Miramos si el elemento tiene los 3 numeros inciales (peso del termino de taxonomia o la imagen de galeria)
  			$item_weight = (int) substr($folder_item, 0, $first_slash_pos);
  			$have_weight = (
  					($first_slash_pos && $item_weight != 0) ||
  					($first_slash_pos && $item_weight == 0 && substr($folder_item, 0, 1) == '0' && substr($folder_item, 1, 1) == '0' && substr($folder_item, 2, 1) == '0')
  			)? TRUE : FALSE;
  			if($have_weight){
  				$item_name = str_replace("_", " ", substr($folder_item, $first_slash_pos+1));
  				//Check if the new item is taxonomy structure or gallery image
  				if(is_dir($new_path)){
  					$parent_id = ($level != 0 && isset($parents_ids[$level-1]))? $parents_ids[$level-1][count($parents_ids[$level-1])-1] : NULL;
  					//Check if taxonomy term exist
  					$taxonomy_tree = taxonomy_get_tree($vid);
  					$term_exist = FALSE;
  					$taxonomy_term_exist = NULL;
  					foreach($taxonomy_tree as $taxonomy_item){
  						//Check if is same name and the same parent id
  						$taxonomy_item_parents = $taxonomy_item->parents;
  						$parent_id_compare = (isset($parent_id) && $parent_id != NULL)? $parent_id : 0;
  						//dpm($taxonomy_item->name.'||'.$item_name.'|||||'.$taxonomy_item_parents[0].'||'.$parent_id_compare);
  						if($taxonomy_item->name == $item_name && $taxonomy_item_parents[0] == $parent_id_compare){
  							$term_exist = TRUE;
  							$taxonomy_term_exist = $taxonomy_item;
  							//dpm('TERM EXIST!!! ('.$item_name.')');
  							break;
  						}
  					}
  					$term = NULL;
  					
  					$markup_msg = '';
  					for($xlev = $level; $xlev > 0; $xlev--) $markup_msg .= ' --- ';
  					$markup_msg .= $item_name;
  					
  					if($term_exist){
  						//Update the item weight
  						$term = (object)$taxonomy_term_exist;
  						$term->weight = $item_weight;
  						$markup_msg .= ' <span style="color:#F00">(EXISTING CATEGORY)</span><br/>';
  					}else{
  						
  						//Create a user friendly path in the path field created by pathauto
  						//$term_path = '';
  						//if($level != 0){
  							//$level_parent_term = taxonomy_term_load($parent_id);
  							//$term_path = $level_parent_term->path . '/';
  						//}
  						//$term_path .= strtolower(str_replace(' ', '-', $item_name));
  						//dpm($term_path);
  						//The field in the term item when 'pathauto' is enabled is called 'path'
  						
  						//Save the taxonomy term
  						$term = (object) array(
  								'vid' => $vid,
  								'name' => $item_name,
  								'weight' => $item_weight,
  								'parent' => $parent_id,
  						);
  						$markup_msg .= ' <span style="color:#0F0">(NEW CATEGORY)</span><br/>';
  					}
  					taxonomy_term_save($term);
  					//Store the new term id in the parents_ids array
  					$term_id = $term->tid;
  					if(isset($parents_ids[$level])) $parents_ids[$level][] = $term_id;
  					else $parents_ids[$level] = array($term_id);
  					
  					$function_resp[] = array(
  						'#type' => 'markup',
  						'#markup' => $markup_msg,
  					);
  					//dpm($term);
  					//dpm("TAXONOMY TERM: ".$item_name."||".$parent_id."||".$level);
  
  
  					$new_path .= "/";
  					$this->scan_folder($new_path, $vid, $parents_ids, $function_resp, $level+1);
  				}else{
  					//Gallery entity image
  					if($gallery_id != 0){
  						//Retrieve the gallery entity item
  						$gallery_entity_query = entity_load('gallery_entity', array($gallery_id), array(), FALSE);
  						$gallery_entity_parent = (count($gallery_entity_query) != 0)? reset($gallery_entity_query) : NULL;
  						if($gallery_entity_parent != NULL){
  							//Check if current gallery have images and get or construct it.
  							$gallery_have_images = isset($gallery_entity_parent->gallery_image) && isset($gallery_entity_parent->gallery_image[LANGUAGE_NONE]);
  							$gallery_image_array = ($gallery_have_images)? $gallery_entity_parent->gallery_image[LANGUAGE_NONE] : array();
  							// Create managed File object and associate with Image field.
  							$number = '';
  							if(count($gallery_image_array) < 9) $number = '00'.(count($gallery_image_array)+1);
  							elseif(count($gallery_image_array) >= 9 && count($gallery_image_array) < 99) $number = '0'.(count($gallery_image_array)+1);
  							elseif(count($gallery_image_array) >= 99) $number = (count($gallery_image_array)+1);
  							$image_title = $gallery_entity_parent->name." ".$number;
  							$file = (object) array(
  									'uid' => 1,
  									'uri' => $new_path,
  									'filename' => str_replace(" ", "_", $item_name),
  									'filemime' => file_get_mimetype($new_path),
  									'status' => 1,
  									'title' => $image_title,
  							);
  							// We save the file to the root of the files directory.
  							$file = file_move($file, 'public://fashion_show/');
  							$file_ext = substr($new_path, strrpos($new_path, '.'));
  							$file->filename = str_replace(" ", "_", $gallery_entity_parent->name).'_'.$file->fid.$file_ext;
  							$file = file_save($file);
  							//dpm($file);
  							$field_info_array = (array)$file;
  							//dpm($field_info_array);
  							
  							//Añadimos las imagenes al disenyador
  							
  							//$gallery_wrapper = entity_metadata_wrapper('gallery_entity', $gallery_entity_parent);
  							//$gallery_wrapper->gallery_image[] = $field_info_array;
  							//$gallery_wrapper->save();
  							//$gallery_entity_parent = $gallery_wrapper->value();	
  							
  							//$gallery_image_array[LANGUAGE_NONE][] = $field_info_array;
  							array_push($gallery_image_array, $field_info_array);
  							//dpm($gallery_image_array);
  							$gallery_entity_parent->gallery_image = array(LANGUAGE_NONE => $gallery_image_array);
  							//Update the gallery entity
  							entity_save('gallery_entity', $gallery_entity_parent);
  							// CON ENTITY API SE GUARDA EL file_usage() AUTOMATICAMENTE (FILE MODULE)
  							//$gallery_entity_parent = $this->save($gallery_entity_parent);
  							//file_usage_add($file, 'gallery_entity', 'gallery_entity', $gallery_entity_parent->gid);
  							
  							
  							//dpm($gallery_entity_parent);
  							//dpm("GALLERY IMAGE: ".$item_name."||".$level."|| PATH: ".$new_path);
  						}
  					}
  				}
  			}else{
  				//Gallery ITEM
  				$item_name = str_replace("_", " ", $folder_item);
  				if(is_dir($new_path)){
  					$parent_id = ($level != 0 && isset($parents_ids[$level-1]))? $parents_ids[$level-1][count($parents_ids[$level-1])-1] : NULL;
  					$gallery_category = (isset($parent_id) && $parent_id != NULL)? array(LANGUAGE_NONE => array(0 => array('tid' => (int)$parent_id))) : NULL;
  					$query = new EntityFieldQuery();
  					$query->entityCondition('entity_type', 'gallery_entity')
  					->entityCondition('bundle', 'fashion_show')
  					->propertyCondition('name', $item_name)
  					->fieldCondition('gallery_category', 'tid', $parent_id, '=');
  					//->addMetaData('account', user_load(1));
  					$result = $query->execute();
  					$gallery_item = $this->create(array('type' => 'fashion_show'));
  					
  					$markup_msg = '';
  					for($xlev = $level; $xlev > 0; $xlev--) $markup_msg .= ' --- ';
  					$markup_msg .= $item_name;
  					
  					if(count($result) == 0){
  						//The gallery item does not exist. Create new one.
  						$gallery_item->name = $item_name;
  						$gallery_item->gallery_category = $gallery_category;
  						entity_save('gallery_entity', $gallery_item);
  						//$gallery_item = $this->save($gallery_item);
  						
  						$markup_msg .= ' <span style="color:#0F0">(NEW GALLERY)</span><br/>';
  						//dpm($gallery_item);
  						//dpm("DESIGNER NAME: ".$item_name."||".$level);
  					}else{
  						//The gallery item exist.
  						$original_gallery = (object)reset($result['gallery_entity']);
  						$gallery_item->gid = $original_gallery->gid;
  						
  						$markup_msg .= ' <span style="color:#F00">(EXISTING GALLERY)</span><br/>';
  						//dpm('GALLERY ITEM EXIST!!! ('.$item_name.')');
  					}
  					//Scan the next folder (designer images)
  					
  					$function_resp[] = array(
  						'#type' => 'markup',
  						'#markup' => $markup_msg,
  					);
  					
  					$new_path .= "/";
  					$ftp_next_folder = scandir($new_path);
  					$num_images = count($ftp_next_folder)-2;
  					if($num_images){
  						$markup_img_msg = '';
  						for($xlev = ($level+1); $xlev > 0; $xlev--) $markup_img_msg .= ' --- ';
  						$markup_img_msg .= '<span style="color:#0F0">'.$num_images.' images in the gallery</span><br/>';
  						$function_resp[] = array(
  							'#type' => 'markup',
  							'#markup' => $markup_img_msg,
  						);
  					}
  					
  					$this->scan_folder($new_path, $vid, $parents_ids, $function_resp, $level+1, $gallery_item->gid);
  				}
  			}
  		}
  	}
  }
  
  
}

/**
 * GalleryEntity Views Controller class.
 */
class GalleryEntityViewsController extends EntityDefaultViewsController {

	/**
	 * Edit or add extra fields to views_data().
	 */
	public function views_data() {
		$data = parent::views_data();

		// Add your custom data here

		/*
		 * Example: change the handler of a field
		* if the 'created' field is a unix timestamp in the database,
		* Entity API will set the handler to views_handler_field_numeric,
		* change this to the views date handler
		*/
		$data['gallery_entity']['created']['field']['handler'] = 'views_handler_field_date';

		return $data;
	}
}

class GalleryEntityTypeController extends EntityAPIControllerExportable {
   public function create(array $values = array()) {
    $values += array(
      'label' => '',
      'description' => '',
    );
    return parent::create($values);
  }

  /**
   * Save gallery Type.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    parent::save($entity, $transaction);
    // Rebuild menu registry. We do not call menu_rebuild directly, but set
    // variable that indicates rebuild in the end.
    // @see http://drupal.org/node/1399618
    variable_set('menu_rebuild_needed', TRUE);
  }
}

/**
 * UI controller for gallery Type.
 */
class GalleryEntityTypeUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage gallery types.';
    return $items;
  }
}

/**
 * Gallery class.
 */
class GalleryEntity extends Entity {
  protected function defaultLabel() {
    return $this->name;
  }

  protected function defaultUri() {
    return array('path' => 'gallery/' . $this->identifier());
  }
}

/**
 * Gallery Type class.
 */
class GalleryEntityType extends Entity {
  public $type;
  public $label;
  public $weight = 0;

  public function __construct($values = array()) {
    parent::__construct($values, 'gallery_entity_type');
  }

  function isLocked() {
    return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }
}
