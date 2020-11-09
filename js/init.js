
// 
var nav = $(".navigation");

// $(window).scroll(function() {
//     if (nav.offset().top < 150) {
//         nav.addClass("fold");
//     } else {
//         nav.removeClass("fold");
//     }
// });
// 

// 
		

if( $( "#about" ).hasClass( 'active' ) ){
	$('.navigation > .btn-group > .btn').removeClass('in');
	$('.navigation > .btn-group > .btn[name=about]').addClass('in');
} else{
	$('.navigation > .btn-group > .btn[name=about]').removeClass('in');			
}

// 
$(document).ready(function(){

		$('a[role=tab]').on('click',function(){

			// if( $( "#about" ).is( '.active' ) ){
			// 	$('.navigation > .btn-group > .btn').removeClass('in');
			// 	$('.navigation > .btn-group > .btn[name=about]').addClass('in');
			// }

			$('.navigation > .btn-group > .btn').removeClass('in');
			$(this).addClass('in');
		});


		$("a[role=tab]").click(function() {
		    $('html, body').animate({
		        scrollTop: $(".navigation").offset().top
		    }, 1000);
		});

		$('#menu-trigger , #sidenav a').on('click',function(){
			$('#sidenav').toggle();
			// $('body').css('overflow','hidden');
		});
});