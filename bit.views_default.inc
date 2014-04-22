<?php

function bit_views_default_views(){
	$view              = new view();
	$view->name        = 'bit_content';
	$view->description = '';
	$view->tag         = 'default';
	$view->base_table  = 'bit';
	$view->human_name  = 'Bit Content';
	$view->core        = 7;
	$view->api_version = '3.0';
	$view->disabled    = false; /* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler                                                                 = $view->new_display( 'default', 'Master', 'default' );
	$handler->display->display_options['title']                              = 'Bit Content';
	$handler->display->display_options['use_more_always']                    = false;
	$handler->display->display_options['access']['type']                     = 'perm';
	$handler->display->display_options['access']['perm']                     = 'edit any bit entities';
	$handler->display->display_options['cache']['type']                      = 'none';
	$handler->display->display_options['query']['type']                      = 'views_query';
	$handler->display->display_options['exposed_form']['type']               = 'basic';
	$handler->display->display_options['pager']['type']                      = 'full';
	$handler->display->display_options['pager']['options']['items_per_page'] = '50';
	$handler->display->display_options['style_plugin']                       = 'table';
	$handler->display->display_options['style_options']['columns']           = array(
		'btid'      => 'btid',
		'title'     => 'title',
		'type'      => 'type',
		'changed'   => 'changed',
		'nothing'   => 'nothing',
		'nothing_1' => 'nothing',
	);
	$handler->display->display_options['style_options']['default']           = '-1';
	$handler->display->display_options['style_options']['info']              = array(
		'btid'      => array(
			'sortable'           => 1,
			'default_sort_order' => 'asc',
			'align'              => '',
			'separator'          => '',
			'empty_column'       => 0,
		),
		'title'     => array(
			'sortable'           => 1,
			'default_sort_order' => 'asc',
			'align'              => '',
			'separator'          => '',
			'empty_column'       => 0,
		),
		'type'      => array(
			'sortable'           => 1,
			'default_sort_order' => 'asc',
			'align'              => '',
			'separator'          => '',
			'empty_column'       => 0,
		),
		'changed'   => array(
			'sortable'           => 1,
			'default_sort_order' => 'asc',
			'align'              => '',
			'separator'          => '',
			'empty_column'       => 0,
		),
		'nothing'   => array(
			'align'        => '',
			'separator'    => '&nbsp;&nbsp;&nbsp;',
			'empty_column' => 0,
		),
		'nothing_1' => array(
			'align'        => '',
			'separator'    => '',
			'empty_column' => 0,
		),
	);
	/* Header: Global: Text area */
	$handler->display->display_options['header']['area']['id']      = 'area';
	$handler->display->display_options['header']['area']['table']   = 'views';
	$handler->display->display_options['header']['area']['field']   = 'area';
	$handler->display->display_options['header']['area']['content'] = '<ul class="action-links"><li><a href="/bit/add">Add bit</a></li></ul>';
	$handler->display->display_options['header']['area']['format']  = 'full_html';
	/* Field: Bit: Bit ID */
	$handler->display->display_options['fields']['btid']['id']    = 'btid';
	$handler->display->display_options['fields']['btid']['table'] = 'bit';
	$handler->display->display_options['fields']['btid']['field'] = 'btid';
	/* Field: Bit: Title */
	$handler->display->display_options['fields']['title']['id']                 = 'title';
	$handler->display->display_options['fields']['title']['table']              = 'bit';
	$handler->display->display_options['fields']['title']['field']              = 'title';
	$handler->display->display_options['fields']['title']['alter']['make_link'] = true;
	$handler->display->display_options['fields']['title']['alter']['path']      = 'bit/[btid]';
	/* Field: Bit: Type */
	$handler->display->display_options['fields']['type']['id']    = 'type';
	$handler->display->display_options['fields']['type']['table'] = 'bit';
	$handler->display->display_options['fields']['type']['field'] = 'type';
	/* Field: Bit: Date changed */
	$handler->display->display_options['fields']['changed']['id']                 = 'changed';
	$handler->display->display_options['fields']['changed']['table']              = 'bit';
	$handler->display->display_options['fields']['changed']['field']              = 'changed';
	$handler->display->display_options['fields']['changed']['label']              = 'Updated';
	$handler->display->display_options['fields']['changed']['date_format']        = 'custom';
	$handler->display->display_options['fields']['changed']['custom_date_format'] = 'F j, Y, g:i a';
	/* Field: Global: Custom text */
	$handler->display->display_options['fields']['nothing']['id']            = 'nothing';
	$handler->display->display_options['fields']['nothing']['table']         = 'views';
	$handler->display->display_options['fields']['nothing']['field']         = 'nothing';
	$handler->display->display_options['fields']['nothing']['label']         = 'Operations';
	$handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="/bit/[btid]/edit">Edit</a>';
	/* Field: Global: Custom text */
	$handler->display->display_options['fields']['nothing_1']['id']                  = 'nothing_1';
	$handler->display->display_options['fields']['nothing_1']['table']               = 'views';
	$handler->display->display_options['fields']['nothing_1']['field']               = 'nothing';
	$handler->display->display_options['fields']['nothing_1']['label']               = '';
	$handler->display->display_options['fields']['nothing_1']['alter']['text']       = '<a href="/bit/[btid]/delete">Delete</a>';
	$handler->display->display_options['fields']['nothing_1']['element_label_colon'] = false;
	/* Sort criterion: Bit: Date changed */
	$handler->display->display_options['sorts']['changed']['id']    = 'changed';
	$handler->display->display_options['sorts']['changed']['table'] = 'bit';
	$handler->display->display_options['sorts']['changed']['field'] = 'changed';
	$handler->display->display_options['sorts']['changed']['order'] = 'DESC';
	/* Filter criterion: Bit: Title */
	$handler->display->display_options['filters']['title']['id']                       = 'title';
	$handler->display->display_options['filters']['title']['table']                    = 'bit';
	$handler->display->display_options['filters']['title']['field']                    = 'title';
	$handler->display->display_options['filters']['title']['operator']                 = 'contains';
	$handler->display->display_options['filters']['title']['exposed']                  = true;
	$handler->display->display_options['filters']['title']['expose']['operator_id']    = 'title_op';
	$handler->display->display_options['filters']['title']['expose']['label']          = 'Title';
	$handler->display->display_options['filters']['title']['expose']['operator']       = 'title_op';
	$handler->display->display_options['filters']['title']['expose']['identifier']     = 'title';
	$handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
		2 => '2',
		1 => 0,
	);
	/* Filter criterion: Bit: Type */
	$handler->display->display_options['filters']['type']['id']                       = 'type';
	$handler->display->display_options['filters']['type']['table']                    = 'bit';
	$handler->display->display_options['filters']['type']['field']                    = 'type';
	$handler->display->display_options['filters']['type']['exposed']                  = true;
	$handler->display->display_options['filters']['type']['expose']['operator_id']    = 'type_op';
	$handler->display->display_options['filters']['type']['expose']['label']          = 'Type';
	$handler->display->display_options['filters']['type']['expose']['operator']       = 'type_op';
	$handler->display->display_options['filters']['type']['expose']['identifier']     = 'type';
	$handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
		2 => '2',
		1 => 0,
	);

	/* Display: Page */
	$handler                                                          = $view->new_display( 'page', 'Page', 'page' );
	$handler->display->display_options['path']                        = 'admin/content/bits';
	$handler->display->display_options['menu']['type']                = 'tab';
	$handler->display->display_options['menu']['title']               = 'Bits';
	$handler->display->display_options['menu']['weight']              = '0';
	$handler->display->display_options['menu']['context']             = 0;
	$handler->display->display_options['menu']['context_only_inline'] = 0;
	$handler->display->display_options['tab_options']['weight']       = '0';

	$views[$view->name] = $view;

  return $views;
}