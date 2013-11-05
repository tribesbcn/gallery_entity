<?php

/**
 * Gallery view callback.
 */
function gallery_entity_view($gallery, $view_mode = 'full') {
  drupal_set_title(entity_label('gallery_entity', $gallery));
  $ev = entity_view('gallery_entity', array(entity_id('gallery_entity', $gallery) => $gallery), $view_mode);
  //dpm($ev);
  return $ev;
}

/**
 * Create ZIP Gallery callback.
 */
function gallery_entity_zip_gallery($gallery, $view_mode = 'full') {
	//drupal_set_title(entity_label('gallery_entity', $gallery));
	if($gallery != NULL){
		$gallery_have_images = isset($gallery->gallery_image) && isset($gallery->gallery_image[LANGUAGE_NONE]);
		$gallery_image_array = ($gallery_have_images)? $gallery->gallery_image[LANGUAGE_NONE] : array();
		//dpm($gallery_image_array);
		$archive_uri = 'private://viewfashion_gallery_' . REQUEST_TIME . '.zip';
		$zip = new ZipArchive;
		if ($zip->open(drupal_realpath($archive_uri), ZipArchive::CREATE) === TRUE) {
			foreach ($gallery_image_array as $file) {
				$zip->addFile(drupal_realpath($file['uri']), $file['filename']);
			}
			$zip->close();
			drupal_set_message(t('Zip archive successfully created. !link', array('!link' => l(t('DOWNLOAD ZIP'), file_create_url($archive_uri)))));
			//Save message to system log.
			$gallery_id = $gallery->gid;
			global $user;
			$user_id = $user->uid;
			watchdog('gallery_entity', 'Downloaded gallery: %gallery_id by user: %user_id', array('%gallery_id' => $gallery_id, '%user_id' => $user_id), WATCHDOG_INFO);
		}else{
			drupal_set_message(t('Error creating Zip archive.'), 'error');
		}
	}
	
	$ev = entity_view('gallery_entity', array(entity_id('gallery_entity', $gallery) => $gallery), $view_mode);
	//dpm($ev);
	return $ev;
}
/**
 * MY Selection view callback.
 */
function gallery_entity_view_selected_images(){
	$my_selection = (isset($_SESSION['my_selection']) && $_SESSION['my_selection'] != NULL)? $_SESSION['my_selection'] : array();
	//dpm($my_selection);	
	$variables = array(
			'images' => $my_selection,
	);
	$content['my_selection'] = array(
			'#markup' => theme('my_selection', $variables),
			'#weight' => 1,
	);
	return $content;
}
/**
 * Add Gallery image to MY Selection callback.
 */
function gallery_entity_add_image_to_selected($image_fid, $type = 'ajax'){
	$file = file_load($image_fid);
	//dpm($file);
	$my_selection = (isset($_SESSION['my_selection']) && $_SESSION['my_selection'] != NULL)? $_SESSION['my_selection'] : array();
	$my_selection[$image_fid] = $file;
	//dpm($my_selection);
	$_SESSION['my_selection'] = $my_selection;
	if($type == 'ajax'){
		//drupal_add_library('system', 'drupal.ajax');
		$image_remove_selection_url = '/my_selection/remove/'.$image_fid;
		//$remove_link = l(t('Remove from selection'), $image_add_selection_url, array('attributes' => array('class' => 'use-ajax')));
		$star_on_img = '<img src="/'.drupal_get_path('module', 'gallery_entity').'/img/star_on.png'.'" alt="'.t('Remove from selection').'" />';
		$remove_link = '<a href="'.$image_remove_selection_url.'" class="use-ajax">'.$star_on_img.'</a>';
		$selector_id = 'image-'.$image_fid.'-link';
		$jquery_selector_id = '#'.$selector_id;
		$output = '<span id="'.$selector_id.'" class="image-link">'.$remove_link.'</span>';
		$commands = array();
		$commands[] = ajax_command_replace($jquery_selector_id, $output);
		$page = array('#type' => 'ajax', '#commands' => $commands);
		ajax_deliver($page);
	}else{
		$content = array();
		return $content;
	}
}
/**
 * Remove Gallery image fron MY Selection callback.
 */
function gallery_entity_remove_image_from_selected($image_fid, $type = 'ajax'){
	$my_selection = (isset($_SESSION['my_selection']) && $_SESSION['my_selection'] != NULL)? $_SESSION['my_selection'] : array();
	if(isset($my_selection) && isset($my_selection[$image_fid])) unset($my_selection[$image_fid]);
	$_SESSION['my_selection'] = $my_selection;
	if($type == 'ajax'){
		//drupal_add_library('system', 'drupal.ajax');
		$image_add_selection_url = '/my_selection/add/'.$image_fid;
		//$add_link = l(t('Add to selection'), $image_add_selection_url, array('attributes' => array('class' => 'use-ajax')));
		$star_off_img = '<img src="/'.drupal_get_path('module', 'gallery_entity').'/img/star_off.png'.'" alt="'.t('Add to selection').'" />';
		$add_link = '<a href="'.$image_add_selection_url.'" class="use-ajax">'.$star_off_img.'</a>';
		$selector_id = 'image-'.$image_fid.'-link';
		$jquery_selector_id = '#'.$selector_id;
		$output = '<span id="'.$selector_id.'" class="image-link">'.$add_link.'</span>';
		$commands = array();
		$commands[] = ajax_command_replace($jquery_selector_id, $output);
		$page = array('#type' => 'ajax', '#commands' => $commands);
		ajax_deliver($page);
	}else{
		$content = array();
		return $content;
	}
}

/**
 * Empty MY Selection callback.
 */
function gallery_entity_empty_selection(){
	$_SESSION['my_selection'] = array();
	$content = array();
	return $content;
}

/**
 * Create ZIP MY Selection callback.
 */
function gallery_entity_zip_selection(){
	$my_selection = $_SESSION['my_selection'];
	//dpm($my_selection);
	$archive_uri = 'private://viewfashion_selection_' . REQUEST_TIME . '.zip';
	$zip = new ZipArchive;
	if ($zip->open(drupal_realpath($archive_uri), ZipArchive::CREATE) === TRUE) {
		$num_pictures = 0;
		foreach ($my_selection as $file) {
			$zip->addFile(drupal_realpath($file->uri), $file->filename);
			$num_pictures++;
		}
		$zip->close();
		drupal_set_message(t('Zip archive successfully created. !link', array('!link' => l(t('DOWNLOAD ZIP'), file_create_url($archive_uri)))));
		//Save message to system log.
		global $user;
		$user_id = $user->uid;
		watchdog('gallery_entity', 'Downloaded selection with %num_pictures images by user: %user_id', array('%num_pictures' => $num_pictures, '%user_id' => $user_id), WATCHDOG_INFO);
	}else{
		drupal_set_message(t('Error creating Zip archive.'), 'error');
	}
	$variables = array(
		'images' => $my_selection,
	);
	$content['my_selection'] = array(
		'#markup' => theme('my_selection', $variables),
		'#weight' => 1,
	);
	return $content;
}
