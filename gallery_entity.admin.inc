<?php

/**
 * Generates the gallery type editing form.
 */
function gallery_entity_type_form($form, &$form_state, $gallery_type, $op = 'edit') {

  if ($op == 'clone') {
    $gallery_type->label .= ' (cloned)';
    $gallery_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $gallery_type->label,
    '#description' => t('The human-readable name of this gallery type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($gallery_type->type) ? $gallery_type->type : '',
    '#maxlength' => 32,
    '#disabled' => $gallery_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'gallery_entity_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this gallery type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#default_value' => isset($gallery_type->description) ? $gallery_type->description : '',
    '#description' => t('Description about the gallery type.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save gallery type'),
    '#weight' => 40,
  );

  if (!$gallery_type->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete gallery type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('gallery_entity_type_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Submit handler for creating/editing gallery_type.
 */
function gallery_entity_type_form_submit(&$form, &$form_state) {
  $gallery_type = entity_ui_form_submit_build_entity($form, $form_state);
  //dpm($gallery_type);
  // Save and go back.
  gallery_entity_type_save($gallery_type);

  // Redirect user back to list of gallery types.
  $form_state['redirect'] = 'admin/structure/gallery-types';
}

function gallery_entity_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/gallery-types/' . $form_state['gallery_entity_type']->type . '/delete';
}

/**
 * Gallery type delete form.
 */
function gallery_entity_type_form_delete_confirm($form, &$form_state, $gallery_type) {
  $form_state['gallery_type'] = $gallery_type;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['gallery_type_id'] = array('#type' => 'value', '#value' => entity_id('gallery_entity_type' ,$gallery_type));
  return confirm_form($form,
    t('Are you sure you want to delete gallery type %title?', array('%title' => entity_label('gallery_type', $gallery_type))),
    'gallery/' . entity_id('gallery_entity_type' ,$gallery_type),
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Gallery type delete form submit handler.
 */
function gallery_entity_type_form_delete_confirm_submit($form, &$form_state) {
  $gallery_type = $form_state['gallery_type'];
  gallery_entity_type_delete($gallery_type);

  watchdog('gallery_entity_type', '@type: deleted %title.', array('@type' => $gallery_type->type, '%title' => $gallery_type->label));
  drupal_set_message(t('@type %title has been deleted.', array('@type' => $gallery_type->type, '%title' => $gallery_type->label)));

  $form_state['redirect'] = 'admin/structure/gallery-types';
}

/**
 * Page to select gallery Type to add new gallery.
 */
function gallery_entity_admin_add_page() {
  $items = array();
  foreach (gallery_entity_types() as $gallery_type_key => $gallery_type) {
    $items[] = l(entity_label('gallery_entity_type', $gallery_type), 'gallery/add/' . $gallery_type_key);
  }
  return array('list' => array('#theme' => 'item_list', '#items' => $items, '#title' => t('Select type of gallery to create.')));
}

/**
 * Page with results of structure and image import.
 */
function gallery_entity_admin_import_folder() {
	$vocabularies = taxonomy_vocabulary_get_names();
	//die(serialize($vocabularies));
	//$pos = array_search('gallery_category_test', $vocabularies);
	$vid = FALSE;
	if(isset($vocabularies['gallery_category'])){
		$voc_obj = (object) $vocabularies['gallery_category'];
		$vid = $voc_obj->vid;
	}
	if(!$vid){
		// arrays are more convenient to initialize
		$vocabulary = array(
			'name' => t('Gallery Category'),
			'machine_name' => 'gallery_category',
			'description' => t('Taxonomy categorization for gallery items'),
			'hierarchy' => 1,
			'module' => 'gallery_entity',
			'weight' => 1,
		);
		$vocabulary = (object) $vocabulary;
		taxonomy_vocabulary_save($vocabulary);
		$vid = $vocabulary->vid;
	}
	
	$folder = $_SERVER['DOCUMENT_ROOT']."/FTP_ITEMS/";
	$parents_ids = array();
	$scan_folder_info = array();
	$folder_info = entity_get_controller('gallery_entity')->scan_folder($folder, $vid, $parents_ids, $scan_folder_info, 0);
	//dpm($parents_ids);
	
	//$content = array();
	$content = $scan_folder_info;
	$content[] = array(
		'#type' => 'markup',
		'#markup' => '<h3>Scan Folder Finished</h3>',
	);
	return $content;
}

/**
 * JSON call for user autocomplete 
 */
function gallery_entity_admin_system_user_autocomplete($gallery_id, $json=TRUE) {
	$matches = array();
	$result = db_select('users')->fields('users', array('uid', 'name'))->condition('uid', 1, '>')->range(0, 10)->execute();
	$subquery_string = 'SELECT gu.uid FROM {gallery_entity_user_privilege} gu WHERE gu.gid = :gid';
	$query_string = 'SELECT u.uid, u.name FROM {users} u WHERE u.uid > 1 AND u.uid NOT IN ('.$subquery_string.') ORDER BY u.name';
	$result = db_query($query_string, array(':gid' => $gallery_id));
	foreach ($result as $user) {
		$matches[$user->uid] = check_plain($user->name);
	}
	if($json) drupal_json_output($matches);
	else return $matches;
}

function gallery_entity_admin_gallery_user_autocomplete($gallery_id, $json=TRUE) {
	$matches = array();
	$result = db_select('gallery_entity_user_privilege')->fields('gallery_entity_user_privilege', array('uid', 'name'))->condition('gid', $gallery_id, '=')->orderBy('name', 'ASC')->execute();
	foreach ($result as $user) {
		$matches[$user->uid] = check_plain($user->name);
	}
	if($json) drupal_json_output($matches);
	else return $matches;
}

/**
 * Add new gallery page callback.
 */
function gallery_entity_add($type) {
  $gallery_type = gallery_entity_types($type);

  $gallery = entity_create('gallery_entity', array('type' => $type));
  drupal_set_title(t('Create @name', array('@name' => entity_label('gallery_type', $gallery_type))));

  $output = drupal_get_form('gallery_entity_form', $gallery);

  return $output;
}

/**
 * gallery Form.
 */
function gallery_entity_form($form, &$form_state, $gallery) {
  $form_state['gallery'] = $gallery;

  $form['name'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Name'),
  	'#weight' => 0,
    '#default_value' => $gallery->name,
  );
/*
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $gallery->description,
  );
*/
  $form['uid'] = array(
    '#type' => 'value',
  	'#weight' => 1,
    '#value' => $gallery->uid,
  );
  
  // Node author information for administrators
  $form['author'] = array(
  		'#type' => 'fieldset',
  		'#title' => t('Authoring information'),
  		'#collapsible' => TRUE,
  		'#collapsed' => TRUE,
  		'#attributes' => array(
  			'class' => array('gallery-form-author'),
  		),
  		'#attached' => array(
  			'js' => array(
  				drupal_get_path('module', 'gallery_entity') . '/js/gallery.admin.js',
  				array(
  					'type' => 'setting',
  					'data' => array('anonymous' => variable_get('anonymous', t('Anonymous'))),
  			),
  		),
  	),
  	'#weight' => 90,
  );
  $gallery_creator_user = ($gallery->uid)? user_load($gallery->uid) : FALSE;
  $username = ($gallery_creator_user)? $gallery_creator_user->name : '';
  $form['author']['uid'] = array(
  	'#type' => 'textfield',
  	'#title' => t('Authored by'),
  	'#maxlength' => 60,
  	'#autocomplete_path' => 'user/autocomplete',
  	'#default_value' => $username,
  	'#weight' => -1,
  	'#description' => t('Leave blank for %anonymous.', array('%anonymous' => variable_get('anonymous', t('Anonymous')))),
  );
  
  $form['options'] = array(
  	'#type' => 'fieldset',
  	'#title' => t('Gallery options'),
  	'#collapsible' => TRUE,
  	'#collapsed' => FALSE,
  	'#attributes' => array(
  		'class' => array('gallery-form-options'),
  	),
  		'#attached' => array(
  		'js' => array(drupal_get_path('module', 'gallery_entity') . '/js/gallery.admin.js'),
  	),
  	'#weight' => 95,
  );
  $form['options']['status'] = array(
  		'#type' => 'checkbox',
  		'#title' => t('Published'),
  		'#default_value' => $gallery->status,
  );
  $form['options']['restricted_access'] = array(
  		'#type' => 'checkbox',
  		'#title' => t('Restricted Access'),
  		'#default_value' => $gallery->restricted_access,
  );
  
  if($gallery->restricted_access){
	  $form['permissions'] = array(
	  		'#type' => 'fieldset',
	  		'#title' => t('Gallery permissions'),
	  		'#collapsible' => TRUE,
	  		'#collapsed' => FALSE,
	  		'#prefix' => '<div id="gallery-permissions-div">',
	  		'#suffix' => '</div>',
	  		'#attributes' => array(
	  			'class' => array('gallery-form-permissions'),
	  		),
	  		'#attached' => array(
	  			'js' => array(drupal_get_path('module', 'gallery_entity') . '/js/gallery.admin.js'),
	  		),
	  		'#weight' => 96,
	  );
	  //$system_user_options = gallery_entity_admin_system_user_autocomplete($gallery->gid, FALSE);
	  $form['permissions']['system_users'] = array(
	  		'#type' => 'select',
	  		'#title' => t('System users'),
	  		'#options' => gallery_entity_admin_system_user_autocomplete($gallery->gid, FALSE),
	  		'#multiple' => TRUE,
	  		'#default_value' => '',
	  		'#description' => t('Users that can not access original size images'),
	  		'#weight' => 96,
	  );
	  $form['permissions']['add_selected'] = array(
	  		'#type' => 'button',
	  		'#value' => '>>',
	  		'#weight' => 97,
	  		'#ajax' => array(
	  			'callback' => 'gallery_entity_add_user_to_gallery_callback',
	  			'wrapper' => 'gallery-permissions-div',
	  			'method' => 'replace',
	  			'effect' => 'fade',
	  		),
	  );
	  $form['permissions']['renove_selected'] = array(
	  		'#type' => 'button',
	  		'#value' => '<<',
	  		'#weight' => 98,
	  		'#ajax' => array(
	  			'callback' => 'gallery_entity_remove_user_from_gallery_callback',
	  			'wrapper' => 'gallery-permissions-div',
	  			'method' => 'replace',
	  			'effect' => 'fade',
	  		),
	  );
	  //$gallery_user_options = gallery_entity_admin_gallery_user_autocomplete($gallery->gid, FALSE);
	  $form['permissions']['gallery_users'] = array(
	  		'#type' => 'select',
	  		'#title' => t('Gallery users'),
	  		'#options' => gallery_entity_admin_gallery_user_autocomplete($gallery->gid, FALSE),
	  		'#multiple' => TRUE,
	  		'#default_value' => '',
	  		'#description' => t('Users that can access original size images'),
	  		'#weight' => 99,
	  );
  }
  field_attach_form('gallery_entity', $gallery, $form, $form_state);

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array(
    '#weight' => 99,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save gallery'),
    '#submit' => $submit + array('gallery_entity_form_submit'),
  	'#weight' => 100,
  );

  // Show Delete button if we edit gallery.
  $gallery_id = entity_id('gallery_entity' ,$gallery);
  if (!empty($gallery_id) && gallery_entity_access('edit', $gallery)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('gallery_entity_form_submit_delete'),
    );
  }

  $form['#validate'][] = 'gallery_entity_form_validate';
  return $form;
}

function gallery_entity_add_user_to_gallery_callback($form, &$form_state) {
	//return $form['permissions']['gallery_users'];
	//dpm($form_state);
	//dpm($form);
	$selected_users = $form_state['values']['system_users'];
	//dpm($selected_users);
	$gallery = $form_state['gallery'];
	$gid = $gallery->gid;
	//Recuperamos los valores de los options del formulario
	$system_users_options = $form['permissions']['system_users']['#options'];
	$gallery_users_options = $form['permissions']['gallery_users']['#options'];
	foreach($selected_users as $uid){
		//Guardamos el registro en la BDD
		$user = user_load($uid);
		$username = $user->name;
		$inserted = db_insert('gallery_entity_user_privilege')->fields(array(
			'gid' => $gid,
			'uid' => $uid,
			'name' => $username,
		))->execute();
		//Modificamos los valores de los options del formulario
		unset($system_users_options[$uid]);
		$gallery_users_options[$uid] = $username;
	}
	//Actualizamos los cambios en los options del formulario
	asort($system_users_options);
	asort($gallery_users_options);
	$form['permissions']['system_users']['#options'] = $system_users_options;
	$form['permissions']['gallery_users']['#options'] = $gallery_users_options;
	//dpm($form['permissions']);
	//$form_state['rebuild'] = TRUE;
	return $form['permissions'];
}

function gallery_entity_remove_user_from_gallery_callback($form, &$form_state) {
	//return $form['permissions']['system_users'];
	$selected_users = $form_state['values']['gallery_users'];
	//dpm($selected_users);
	$gallery = $form_state['gallery'];
	$gid = $gallery->gid;
	//Recuperamos los valores de los options del formulario
	$system_users_options = $form['permissions']['system_users']['#options'];
	$gallery_users_options = $form['permissions']['gallery_users']['#options'];
	foreach($selected_users as $uid){
		//Borramos el registro de la BDD
		$and = db_and()->condition('uid', $uid)->condition('gid', $gid);
		$deleted = db_delete('gallery_entity_user_privilege')->condition($and)->execute();
		//Modificamos los valores de los options del formulario
		$user = user_load($uid);
		$username = $user->name;
		unset($gallery_users_options[$uid]);
		$system_users_options[$uid] = $username;
	}
	//Actualizamos los cambios en los options del formulario
	asort($system_users_options);
	asort($gallery_users_options);
	$form['permissions']['system_users']['#options'] = $system_users_options;
	$form['permissions']['gallery_users']['#options'] = $gallery_users_options;
	//$form_state['rebuild'] = TRUE;
	return $form['permissions'];
}

function gallery_entity_form_validate($form, &$form_state) {

}

/**
 * Gallery submit handler.
 */
function gallery_entity_form_submit($form, &$form_state) {
  $gallery = $form_state['gallery'];
  //dpm($gallery);
  //dpm($form);
  //dpm($form_state);
  entity_form_submit_build_entity('gallery_entity', $gallery, $form, $form_state);
  gallery_entity_save($gallery);
  $gallery_uri = entity_uri('gallery_entity', $gallery);
  $form_state['redirect'] = $gallery_uri['path'];
  drupal_set_message(t('Gallery %title saved.', array('%title' => entity_label('gallery_entity', $gallery))));
}

function gallery_entity_form_submit_delete($form, &$form_state) {
  $gallery = $form_state['gallery'];
  $gallery_uri = entity_uri('gallery_entity', $gallery);
  $form_state['redirect'] = $gallery_uri['path'] . '/delete';
}

/**
 * Delete confirmation form.
 */
function gallery_entity_delete_form($form, &$form_state, $gallery) {
  $form_state['gallery'] = $gallery;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['gallery_type_id'] = array('#type' => 'value', '#value' => entity_id('gallery_entity' ,$gallery));
  $gallery_uri = entity_uri('gallery_entity', $gallery);
  return confirm_form($form,
    t('Are you sure you want to delete gallery %title?', array('%title' => entity_label('gallery_entity', $gallery))),
    $gallery_uri['path'],
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Delete form submit handler.
 */
function gallery_entity_delete_form_submit($form, &$form_state) {
  $gallery = $form_state['gallery'];
  //Gallery entity deletion
  gallery_entity_delete($gallery);
  drupal_set_message(t('Gallery %name deleted.', array('%name' => entity_label('gallery_entity', $gallery))));

  $form_state['redirect'] = '<front>';
}
