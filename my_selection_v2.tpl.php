<div id="my_selection">
	<?php foreach($images as $fid => Sfile){ ?>
		<?php 
		$img_url = $file->uri;
		$large_url = image_style_url('large', $img_url);
		$medium_url = image_style_url('medium', $img_url);
		$image_remove_selection_url = '/my_selection/remove/'.$fid;
		$remove_link = l(t('Remove from selection'), $image_remove_selection_url, array('attributes' => array('class' => 'use-ajax')));
		//$remove_link = '<a href="'.$image_remove_selection_url.'" class="use-ajax">'.t("Remove from selection").'</a>';
		?>
		<div class="gallery_entity_image_box">
			<a href="<?=$large_url?>" class="lightbox-processed"><img src="<?=$medium_url?>" class="image_selection"/></a>
			<p align="center"><span id="image-'<?=$fid?>'-link" class="image-link"><?=$remove_link?></span></p>
		</div>
	<?php } ?>
</div>