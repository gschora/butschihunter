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

    fs.watch('./', [], function () {
        if (location)
            location.reload(false);
    });
}