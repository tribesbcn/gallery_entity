<?php

/*
	$view = new view;
	$view->name = 'galleries';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'gallery_entity';
	$view->human_name = 'Galleries';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; //Edit this to true to make a default view disabled initially
	
	// Display: Master 
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Galleries';
	$handler->display->display_options['access']['type'] = 'none';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['query']['options']['query_comment'] = FALSE;
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'full';
	$handler->display->display_options['pager']['options']['items_per_page'] = '10';
	$handler->display->display_options['style_plugin'] = 'table';
	// Header: Global: Text area 
	
	//$handler->display->display_options['header']['area']['id'] = 'area';
	//$handler->display->display_options['header']['area']['table'] = 'views';
	//$handler->display->display_options['header']['area']['field'] = 'area';
	//$handler->display->display_options['header']['area']['empty'] = FALSE;
	//$handler->display->display_options['header']['area']['content'] = '<a href="<?php print url(\'task/add\'); ?>>Add Task</a>';
	//$handler->display->display_options['header']['area']['format'] = 'full_html';
	//$handler->display->display_options['header']['area']['tokenize'] = 0;
	
	// Relationship: Task: Author
	$handler->display->display_options['relationships']['uid']['id'] = 'uid';
	$handler->display->display_options['relationships']['uid']['table'] = 'gallery_entity';
	$handler->display->display_options['relationships']['uid']['field'] = 'uid';
	$handler->display->display_options['relationships']['uid']['label'] = 'Author';
	$handler->display->display_options['relationships']['uid']['required'] = 0;
	// Field: Task: Task ID 
	$handler->display->display_options['fields']['gid']['id'] = 'gid';
	$handler->display->display_options['fields']['gid']['table'] = 'gallery_entity';
	$handler->display->display_options['fields']['gid']['field'] = 'gid';
	// Field: Task: Title
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'gallery_entity';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['name']['alter']['make_link'] = 1;
	$handler->display->display_options['fields']['name']['alter']['path'] = 'task/[gid]';
	$handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['name']['alter']['external'] = 0;
	$handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
	$handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
	$handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['name']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['name']['alter']['html'] = 0;
	$handler->display->display_options['fields']['name']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['name']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['name']['hide_empty'] = 0;
	$handler->display->display_options['fields']['name']['empty_zero'] = 0;
	$handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
	// Field: User: Name
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'users';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['relationship'] = 'uid';
	$handler->display->display_options['fields']['name']['label'] = 'Author';
	$handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['name']['alter']['external'] = 0;
	$handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
	$handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
	$handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['name']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['name']['alter']['html'] = 0;
	$handler->display->display_options['fields']['name']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['name']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['name']['hide_empty'] = 0;
	$handler->display->display_options['fields']['name']['empty_zero'] = 0;
	$handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
	$handler->display->display_options['fields']['name']['link_to_user'] = 1;
	$handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
	$handler->display->display_options['fields']['name']['format_username'] = 1;
	// Field: Task: Date created
	$handler->display->display_options['fields']['created']['id'] = 'created';
	$handler->display->display_options['fields']['created']['table'] = 'gallery_entity';
	$handler->display->display_options['fields']['created']['field'] = 'created';
	$handler->display->display_options['fields']['created']['label'] = 'Created';
	$handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['created']['alter']['external'] = 0;
	$handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
	$handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
	$handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['created']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['created']['alter']['html'] = 0;
	$handler->display->display_options['fields']['created']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['created']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['created']['hide_empty'] = 0;
	$handler->display->display_options['fields']['created']['empty_zero'] = 0;
	$handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
	$handler->display->display_options['fields']['created']['date_format'] = 'short';
	// Field: Global: Custom text
	$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
	$handler->display->display_options['fields']['nothing']['table'] = 'views';
	$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
	$handler->display->display_options['fields']['nothing']['label'] = 'Edit';
	$handler->display->display_options['fields']['nothing']['alter']['text'] = 'Edit';
	$handler->display->display_options['fields']['nothing']['alter']['make_link'] = 1;
	$handler->display->display_options['fields']['nothing']['alter']['path'] = 'gallery/[gid]/edit';
	$handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
	$handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
	$handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
	$handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
	$handler->display->display_options['fields']['nothing']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['nothing']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
	$handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
	$handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 0;
	
	// Display: Page
	$handler = $view->new_display('page', 'Page', 'page');
	$handler->display->display_options['path'] = 'gallery';
	$handler->display->display_options['menu']['type'] = 'normal';
	$handler->display->display_options['menu']['title'] = 'Galleries';
	$handler->display->display_options['menu']['weight'] = '0';
*/

/**
 * Implements hook_views_default_views().
 */
function gallery_entity_views_default_views() {
	$views = array();
	
	$view = new view();
	$view->name = 'galleries';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'gallery_entity';
	$view->human_name = 'Galleries';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
	
	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Galleries';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['access']['perm'] = 'edit any gallery_entity entities';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['query']['options']['query_comment'] = FALSE;
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'full';
	$handler->display->display_options['pager']['options']['items_per_page'] = '25';
	$handler->display->display_options['pager']['options']['offset'] = '0';
	$handler->display->display_options['pager']['options']['id'] = '0';
	$handler->display->display_options['pager']['options']['quantity'] = '9';
	$handler->display->display_options['pager']['options']['tags']['first'] = '« primera';
	$handler->display->display_options['pager']['options']['tags']['previous'] = '‹ anterior';
	$handler->display->display_options['pager']['options']['tags']['next'] = 'siguiente ›';
	$handler->display->display_options['pager']['options']['tags']['last'] = 'última »';
	$handler->display->display_options['style_plugin'] = 'table';
	$handler->display->display_options['style_options']['columns'] = array(
			'views_bulk_operations' => 'views_bulk_operations',
			'gid' => 'gid',
			'name_1' => 'name_1',
			'gallery_category' => 'gallery_category',
			'name' => 'name',
			'created' => 'created',
			'status' => 'status',
			'restricted_access' => 'restricted_access',
			'nothing' => 'nothing',
			'nothing_1' => 'nothing_1',
	);
	$handler->display->display_options['style_options']['default'] = 'gid';
	$handler->display->display_options['style_options']['info'] = array(
			'views_bulk_operations' => array(
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'gid' => array(
					'sortable' => 1,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'name_1' => array(
					'sortable' => 1,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'gallery_category' => array(
					'sortable' => 1,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'name' => array(
					'sortable' => 0,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'created' => array(
					'sortable' => 1,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'status' => array(
					'sortable' => 1,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'restricted_access' => array(
					'sortable' => 0,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'nothing' => array(
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'nothing_1' => array(
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
	);
	/* Relationship: Gallery: Author */
	$handler->display->display_options['relationships']['uid']['id'] = 'uid';
	$handler->display->display_options['relationships']['uid']['table'] = 'gallery_entity';
	$handler->display->display_options['relationships']['uid']['field'] = 'uid';
	$handler->display->display_options['relationships']['uid']['label'] = 'Author';
	/* Field: Bulk operations: Gallery */
	$handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
	$handler->display->display_options['fields']['views_bulk_operations']['table'] = 'gallery_entity';
	$handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
			'action::gallery_entity_convert_to_private_action' => array(
					'selected' => 1,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::gallery_entity_convert_to_public_action' => array(
					'selected' => 1,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::gallery_entity_delete_action' => array(
					'selected' => 1,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::views_bulk_operations_delete_item' => array(
					'selected' => 0,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::system_send_email_action' => array(
					'selected' => 0,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::views_bulk_operations_script_action' => array(
					'selected' => 0,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::views_bulk_operations_modify_action' => array(
					'selected' => 0,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
					'settings' => array(
							'show_all_tokens' => 1,
							'display_values' => array(
									'_all_' => '_all_',
							),
					),
			),
			'action::views_bulk_operations_argument_selector_action' => array(
					'selected' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
					'settings' => array(
							'url' => '',
					),
			),
			'action::gallery_entity_publish_item_action' => array(
					'selected' => 1,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::gallery_entity_unpublish_item_action' => array(
					'selected' => 1,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
	);
	/* Field: Gallery: Gallery ID */
	$handler->display->display_options['fields']['gid']['id'] = 'gid';
	$handler->display->display_options['fields']['gid']['table'] = 'gallery_entity';
	$handler->display->display_options['fields']['gid']['field'] = 'gid';
	$handler->display->display_options['fields']['gid']['label'] = 'Id';
	/* Field: Gallery: Name */
	$handler->display->display_options['fields']['name_1']['id'] = 'name_1';
	$handler->display->display_options['fields']['name_1']['table'] = 'gallery_entity';
	$handler->display->display_options['fields']['name_1']['field'] = 'name';
	$handler->display->display_options['fields']['name_1']['label'] = 'Designer';
	$handler->display->display_options['fields']['name_1']['element_label_colon'] = FALSE;
	/* Field: Gallery: Gallery category */
	$handler->display->display_options['fields']['gallery_category']['id'] = 'gallery_category';
	$handler->display->display_options['fields']['gallery_category']['table'] = 'field_data_gallery_category';
	$handler->display->display_options['fields']['gallery_category']['field'] = 'gallery_category';
	$handler->display->display_options['fields']['gallery_category']['element_label_colon'] = FALSE;
	/* Field: User: Name */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'users';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['relationship'] = 'uid';
	$handler->display->display_options['fields']['name']['label'] = 'Author';
	$handler->display->display_options['fields']['name']['exclude'] = TRUE;
	$handler->display->display_options['fields']['name']['alter']['path'] = 'task/[gid]';
	/* Field: Gallery: Date created */
	$handler->display->display_options['fields']['created']['id'] = 'created';
	$handler->display->display_options['fields']['created']['table'] = 'gallery_entity';
	$handler->display->display_options['fields']['created']['field'] = 'created';
	$handler->display->display_options['fields']['created']['label'] = 'Created';
	$handler->display->display_options['fields']['created']['date_format'] = 'short';
	/* Field: Gallery: Status */
	$handler->display->display_options['fields']['status']['id'] = 'status';
	$handler->display->display_options['fields']['status']['table'] = 'gallery_entity';
	$handler->display->display_options['fields']['status']['field'] = 'status';
	$handler->display->display_options['fields']['status']['label'] = 'Published';
	$handler->display->display_options['fields']['status']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['status']['alter']['text'] = '<img src="/sites/default/files/admin_icons/plus-circle.png" />';
	$handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['status']['empty'] = '<img src="/sites/default/files/admin_icons/minus-circle.png" />';
	$handler->display->display_options['fields']['status']['empty_zero'] = TRUE;
	$handler->display->display_options['fields']['status']['separator'] = '';
	/* Field: Gallery: Restricted_access */
	$handler->display->display_options['fields']['restricted_access']['id'] = 'restricted_access';
	$handler->display->display_options['fields']['restricted_access']['table'] = 'gallery_entity';
	$handler->display->display_options['fields']['restricted_access']['field'] = 'restricted_access';
	$handler->display->display_options['fields']['restricted_access']['label'] = 'Private';
	$handler->display->display_options['fields']['restricted_access']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['restricted_access']['alter']['text'] = '<img src="/sites/default/files/admin_icons/plus-circle.png" />';
	$handler->display->display_options['fields']['restricted_access']['empty'] = '<img src="/sites/default/files/admin_icons/minus-circle.png" />';
	$handler->display->display_options['fields']['restricted_access']['empty_zero'] = TRUE;
	/* Field: Global: Custom text */
	$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
	$handler->display->display_options['fields']['nothing']['table'] = 'views';
	$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
	$handler->display->display_options['fields']['nothing']['label'] = 'Edit';
	$handler->display->display_options['fields']['nothing']['alter']['text'] = 'Edit';
	$handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
	$handler->display->display_options['fields']['nothing']['alter']['path'] = 'gallery/[gid]/edit';
	/* Field: Global: Custom text */
	$handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
	$handler->display->display_options['fields']['nothing_1']['table'] = 'views';
	$handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
	$handler->display->display_options['fields']['nothing_1']['label'] = 'Delete';
	$handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'Delete';
	$handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
	$handler->display->display_options['fields']['nothing_1']['alter']['path'] = 'gallery/[gid]/delete';
	$handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
	/* Filter criterion: Gallery: Type */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'gallery_entity';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
			'fashion_show' => 'fashion_show',
	);
	
	/* Display: Page */
	$handler = $view->new_display('page', 'Page', 'page');
	$handler->display->display_options['path'] = 'gallery';
	$handler->display->display_options['menu']['type'] = 'normal';
	$handler->display->display_options['menu']['title'] = 'Galleries administration';
	$handler->display->display_options['menu']['weight'] = '0';
	$handler->display->display_options['menu']['context'] = 0;
	$handler->display->display_options['menu']['context_only_inline'] = 0;
	$translatables['galleries'] = array(
			t('Master'),
			t('Galleries'),
			t('more'),
			t('Apply'),
			t('Reset'),
			t('Sort by'),
			t('Asc'),
			t('Desc'),
			t('Items per page'),
			t('- All -'),
			t('Offset'),
			t('« primera'),
			t('‹ anterior'),
			t('siguiente ›'),
			t('última »'),
			t('Author'),
			t('Gallery'),
			t('Id'),
			t('.'),
			t(','),
			t('Designer'),
			t('Gallery category'),
			t('Created'),
			t('Published'),
			t('<img src="/sites/default/files/admin_icons/plus-circle.png" />'),
			t('<img src="/sites/default/files/admin_icons/minus-circle.png" />'),
			t('Private'),
			t('Edit'),
			t('Delete'),
			t('Page'),
	);	
	$views['galleries'] = $view;
	
	$view = new view();
	$view->name = 'categories';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'taxonomy_term_data';
	$view->human_name = 'Categories';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
	
	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Categories';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'role';
	$handler->display->display_options['access']['role'] = array(
			3 => '3',
			4 => '4',
	);
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'none';
	$handler->display->display_options['pager']['options']['offset'] = '0';
	$handler->display->display_options['style_plugin'] = 'table';
	$handler->display->display_options['style_options']['columns'] = array(
			'views_bulk_operations' => 'views_bulk_operations',
			'name' => 'name',
			'name_1' => 'name_1',
			'weight' => 'weight',
	);
	$handler->display->display_options['style_options']['default'] = '-1';
	$handler->display->display_options['style_options']['info'] = array(
			'views_bulk_operations' => array(
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'name' => array(
					'sortable' => 1,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'name_1' => array(
					'sortable' => 1,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'weight' => array(
					'sortable' => 0,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
	);
	/* Relationship: Taxonomy term: Parent term */
	$handler->display->display_options['relationships']['parent']['id'] = 'parent';
	$handler->display->display_options['relationships']['parent']['table'] = 'taxonomy_term_hierarchy';
	$handler->display->display_options['relationships']['parent']['field'] = 'parent';
	/* Field: Bulk operations: Taxonomy term */
	$handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
	$handler->display->display_options['fields']['views_bulk_operations']['table'] = 'taxonomy_term_data';
	$handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
	$handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
	$handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
			'action::gallery_entity_convert_category_to_private_action' => array(
					'selected' => 1,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::gallery_entity_convert_category_to_public_action' => array(
					'selected' => 1,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::gallery_entity_delete_gallery_category' => array(
					'selected' => 1,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::views_bulk_operations_delete_item' => array(
					'selected' => 0,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::system_send_email_action' => array(
					'selected' => 0,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::views_bulk_operations_script_action' => array(
					'selected' => 0,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::views_bulk_operations_modify_action' => array(
					'selected' => 0,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
					'settings' => array(
							'show_all_tokens' => 1,
							'display_values' => array(
									'_all_' => '_all_',
							),
					),
			),
			'action::views_bulk_operations_argument_selector_action' => array(
					'selected' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
					'settings' => array(
							'url' => '',
					),
			),
			'action::gallery_entity_publish_category_action' => array(
					'selected' => 1,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::gallery_entity_unpublish_category_action' => array(
					'selected' => 1,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
			'action::pathauto_taxonomy_term_update_action' => array(
					'selected' => 0,
					'postpone_processing' => 0,
					'skip_confirmation' => 0,
					'override_label' => 0,
					'label' => '',
			),
	);
	/* Field: Taxonomy term: Term ID */
	$handler->display->display_options['fields']['tid']['id'] = 'tid';
	$handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
	$handler->display->display_options['fields']['tid']['field'] = 'tid';
	$handler->display->display_options['fields']['tid']['label'] = 'Id';
	$handler->display->display_options['fields']['tid']['separator'] = '';
	/* Field: Taxonomy term: Name */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
	$handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
	$handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
	/* Field: Taxonomy term: Name */
	$handler->display->display_options['fields']['name_1']['id'] = 'name_1';
	$handler->display->display_options['fields']['name_1']['table'] = 'taxonomy_term_data';
	$handler->display->display_options['fields']['name_1']['field'] = 'name';
	$handler->display->display_options['fields']['name_1']['relationship'] = 'parent';
	$handler->display->display_options['fields']['name_1']['label'] = 'Parent';
	/* Field: Taxonomy term: Weight */
	$handler->display->display_options['fields']['weight']['id'] = 'weight';
	$handler->display->display_options['fields']['weight']['table'] = 'taxonomy_term_data';
	$handler->display->display_options['fields']['weight']['field'] = 'weight';
	$handler->display->display_options['fields']['weight']['separator'] = '';
	/* Sort criterion: Taxonomy term: Term ID */
	$handler->display->display_options['sorts']['tid']['id'] = 'tid';
	$handler->display->display_options['sorts']['tid']['table'] = 'taxonomy_term_data';
	$handler->display->display_options['sorts']['tid']['field'] = 'tid';
	/* Filter criterion: Taxonomy term: Vocabulary */
	$handler->display->display_options['filters']['vid']['id'] = 'vid';
	$handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
	$handler->display->display_options['filters']['vid']['field'] = 'vid';
	$handler->display->display_options['filters']['vid']['value'] = array(
			7 => '7',
	);
	
	/* Display: Page */
	$handler = $view->new_display('page', 'Page', 'page');
	$handler->display->display_options['path'] = 'gallery/categories';
	$translatables['categories'] = array(
			t('Master'),
			t('Categories'),
			t('more'),
			t('Apply'),
			t('Reset'),
			t('Sort by'),
			t('Asc'),
			t('Desc'),
			t('Parent'),
			t('Id'),
			t('.'),
			t('Name'),
			t('Weight'),
			t('Page'),
	);
	
	$views['categories'] = $view;
	
	$view = new view();
	$view->name = 'gallery_entity_taxonomy';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'gallery_entity';
	$view->human_name = 'Gallery Entity Taxonomy';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
	
	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = '%1';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['access']['perm'] = 'view gallery_entity entities';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'none';
	$handler->display->display_options['pager']['options']['offset'] = '0';
	$handler->display->display_options['style_plugin'] = 'grid';
	$handler->display->display_options['row_plugin'] = 'fields';
	/* Field: Gallery: Gallery ID */
	$handler->display->display_options['fields']['gid']['id'] = 'gid';
	$handler->display->display_options['fields']['gid']['table'] = 'gallery_entity';
	$handler->display->display_options['fields']['gid']['field'] = 'gid';
	$handler->display->display_options['fields']['gid']['label'] = '';
	$handler->display->display_options['fields']['gid']['exclude'] = TRUE;
	$handler->display->display_options['fields']['gid']['element_label_colon'] = FALSE;
	/* Field: Gallery: Name */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'gallery_entity';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['label'] = '';
	$handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
	$handler->display->display_options['fields']['name']['alter']['path'] = 'gallery/[gid]';
	$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
	/* Contextual filter: Gallery: Gallery category (gallery_category) */
	$handler->display->display_options['arguments']['gallery_category_tid']['id'] = 'gallery_category_tid';
	$handler->display->display_options['arguments']['gallery_category_tid']['table'] = 'field_data_gallery_category';
	$handler->display->display_options['arguments']['gallery_category_tid']['field'] = 'gallery_category_tid';
	$handler->display->display_options['arguments']['gallery_category_tid']['exception']['title'] = 'Todo(s)';
	$handler->display->display_options['arguments']['gallery_category_tid']['title_enable'] = TRUE;
	$handler->display->display_options['arguments']['gallery_category_tid']['title'] = '%1';
	$handler->display->display_options['arguments']['gallery_category_tid']['default_argument_type'] = 'fixed';
	$handler->display->display_options['arguments']['gallery_category_tid']['summary']['number_of_records'] = '0';
	$handler->display->display_options['arguments']['gallery_category_tid']['summary']['format'] = 'default_summary';
	$handler->display->display_options['arguments']['gallery_category_tid']['summary_options']['items_per_page'] = '25';
	$handler->display->display_options['arguments']['gallery_category_tid']['specify_validation'] = TRUE;
	$handler->display->display_options['arguments']['gallery_category_tid']['validate']['type'] = 'taxonomy_term';
	$handler->display->display_options['arguments']['gallery_category_tid']['validate_options']['vocabularies'] = array(
			'gallery_category' => 'gallery_category',
	);
	/* Filter criterion: Gallery: Type */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'gallery_entity';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
			'fashion_show' => 'fashion_show',
	);
	/* Filter criterion: Gallery: Status */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'gallery_entity';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value']['value'] = '1';
	
	/* Display: Page */
	$handler = $view->new_display('page', 'Page', 'page');
	$handler->display->display_options['path'] = 'taxonomy/term/%';
	$translatables['gallery_entity_taxonomy'] = array(
			t('Master'),
			t('%1'),
			t('more'),
			t('Apply'),
			t('Reset'),
			t('Sort by'),
			t('Asc'),
			t('Desc'),
			t('.'),
			t(','),
			t('Todo(s)'),
			t('Page'),
	);
	
	$views['gallery_entity_taxonomy'] = $view;
	
	$view = new view();
	$view->name = 'download_control';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'watchdog';
	$view->human_name = 'Download control';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
	
	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Download control';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'role';
	$handler->display->display_options['access']['role'] = array(
			3 => '3',
			4 => '4',
	);
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'full';
	$handler->display->display_options['pager']['options']['items_per_page'] = '10';
	$handler->display->display_options['style_plugin'] = 'table';
	$handler->display->display_options['style_options']['columns'] = array(
			'variables' => 'variables',
			'wid' => 'wid',
			'message' => 'message',
			'hostname' => 'hostname',
			'timestamp' => 'timestamp',
			'rendered_entity' => 'rendered_entity',
	);
	$handler->display->display_options['style_options']['default'] = 'timestamp';
	$handler->display->display_options['style_options']['info'] = array(
			'variables' => array(
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'wid' => array(
					'sortable' => 0,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'message' => array(
					'sortable' => 1,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'hostname' => array(
					'sortable' => 1,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'timestamp' => array(
					'sortable' => 1,
					'default_sort_order' => 'desc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
			'rendered_entity' => array(
					'align' => '',
					'separator' => '',
					'empty_column' => 0,
			),
	);
	/* Relationship: Watchdog: User */
	$handler->display->display_options['relationships']['uid']['id'] = 'uid';
	$handler->display->display_options['relationships']['uid']['table'] = 'watchdog';
	$handler->display->display_options['relationships']['uid']['field'] = 'uid';
	/* Field: Watchdog: Variables */
	$handler->display->display_options['fields']['variables']['id'] = 'variables';
	$handler->display->display_options['fields']['variables']['table'] = 'watchdog';
	$handler->display->display_options['fields']['variables']['field'] = 'variables';
	$handler->display->display_options['fields']['variables']['label'] = '';
	$handler->display->display_options['fields']['variables']['exclude'] = TRUE;
	$handler->display->display_options['fields']['variables']['element_label_colon'] = FALSE;
	/* Field: Watchdog: Wid */
	$handler->display->display_options['fields']['wid']['id'] = 'wid';
	$handler->display->display_options['fields']['wid']['table'] = 'watchdog';
	$handler->display->display_options['fields']['wid']['field'] = 'wid';
	$handler->display->display_options['fields']['wid']['exclude'] = TRUE;
	$handler->display->display_options['fields']['wid']['element_label_colon'] = FALSE;
	/* Field: Watchdog: Message */
	$handler->display->display_options['fields']['message']['id'] = 'message';
	$handler->display->display_options['fields']['message']['table'] = 'watchdog';
	$handler->display->display_options['fields']['message']['field'] = 'message';
	$handler->display->display_options['fields']['message']['watchdog_message_format'] = 1;
	$handler->display->display_options['fields']['message']['watchdog_message_link'] = 1;
	/* Field: Watchdog: Hostname */
	$handler->display->display_options['fields']['hostname']['id'] = 'hostname';
	$handler->display->display_options['fields']['hostname']['table'] = 'watchdog';
	$handler->display->display_options['fields']['hostname']['field'] = 'hostname';
	$handler->display->display_options['fields']['hostname']['label'] = 'Server name';
	$handler->display->display_options['fields']['hostname']['element_label_colon'] = FALSE;
	/* Field: Watchdog: Timestamp */
	$handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
	$handler->display->display_options['fields']['timestamp']['table'] = 'watchdog';
	$handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
	$handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['timestamp']['date_format'] = 'long';
	/* Field: User: Rendered User */
	$handler->display->display_options['fields']['rendered_entity']['id'] = 'rendered_entity';
	$handler->display->display_options['fields']['rendered_entity']['table'] = 'views_entity_user';
	$handler->display->display_options['fields']['rendered_entity']['field'] = 'rendered_entity';
	$handler->display->display_options['fields']['rendered_entity']['relationship'] = 'uid';
	$handler->display->display_options['fields']['rendered_entity']['label'] = 'User';
	$handler->display->display_options['fields']['rendered_entity']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['rendered_entity']['link_to_entity'] = 1;
	$handler->display->display_options['fields']['rendered_entity']['view_mode'] = 'full';
	$handler->display->display_options['fields']['rendered_entity']['bypass_access'] = 0;
	/* Sort criterion: Watchdog: Timestamp */
	$handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
	$handler->display->display_options['sorts']['timestamp']['table'] = 'watchdog';
	$handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
	$handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
	/* Filter criterion: Watchdog: Type */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'watchdog';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
			'gallery_entity' => 'gallery_entity',
	);
	
	/* Display: Page */
	$handler = $view->new_display('page', 'Page', 'page');
	$handler->display->display_options['path'] = 'download-control';
	$translatables['download_control'] = array(
			t('Master'),
			t('Download control'),
			t('more'),
			t('Apply'),
			t('Reset'),
			t('Sort by'),
			t('Asc'),
			t('Desc'),
			t('Items per page'),
			t('- All -'),
			t('Offset'),
			t('« first'),
			t('‹ previous'),
			t('next ›'),
			t('last »'),
			t('Watchdog - Users'),
			t('Wid'),
			t('.'),
			t(','),
			t('Message'),
			t('Server name'),
			t('Timestamp'),
			t('User'),
			t('Page'),
	);
	
	$views['download_control'] = $view;
	
	return $views;
}