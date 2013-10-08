
(function ($) {
	Drupal.behaviors.gallery_entity = { 
		attach: function (context, settings) {
	       // Cuando se añade el contenido a la página
			$(".image-link").click(function(evento){
				alert("Adding to selection");
			});
		},
		detach: function (context, settings) {
	       // Cuando se elimina el contenido de la página (opcional)
		},
	};
	
})(jQuery);
