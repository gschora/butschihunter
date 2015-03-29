/**
 * starts all functions in die file
 */
(function () {
    autoReloadPage();
})();


/**
 * auto reloads page in node-webkit everytime something is changed
 */
function autoReloadPage() {
    var fs = require('fs');

    fs.watch('./js/', {recursive: true}, function () {
        if (location)
            location.reload(false);
    });
    fs.watch('./views/', {recursive: true}, function () {
        if (location)
            location.reload(false);
    });
}