
(function ($) {

Drupal.behaviors.nodeFieldsetSummaries = {
  attach: function (context) {
	 $('fieldset.gallery-form-author', context).drupalSetSummary(function (context) {
	  var name = $('.form-item-uid input', context).val() || Drupal.settings.anonymous;
	  return Drupal.t('By @name', { '@name': name });
	});
    $('fieldset.gallery-form-options', context).drupalSetSummary(function (context) {
      var vals = [];

      $('input:checked', context).parent().each(function () {
        vals.push(Drupal.checkPlain($.trim($(this).text())));
      });

      if (!$('.form-item-status input', context).is(':checked')) {
        vals.unshift(Drupal.t('Not published'));
      }
      return vals.join(', ');
    });
  }
};

})(jQuery);
