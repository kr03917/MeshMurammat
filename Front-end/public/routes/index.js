var express = require('express');
var router = express.Router();
const path = require('path');
const testAddon = require('./../../build/Release/testaddon.node');
        

/* GET welcome page. */
router.get('/meshmurammat', function(req, res, next) {
  res.sendFile(path.join(__dirname, '/welcome.html'));
  
});

/* GET home page. */

router.get('/home', function(req, res, next) {
  res.sendFile(path.join(__dirname, '/home.html'));
  
  var exec = require('child_process').execFile;

  var fun =function(){
   console.log("fun() start");
   exec(path.join(__dirname, '/mesh.exe'), function(err, data) {  
        console.log(err)
        console.log(data.toString());                       
    });  
}
fun();
});

router.get('/cpp', function(req, res, next) {  
  res.send(testAddon.add(+req.query.a,+req.query.b).toString());
});

router.get('/meshviewer', function(req, res, next) {
  res.sendFile(path.join(__dirname, '/meshViewer.html'));
});

//router.get('/fileupload', function(req, res, next) {  
//  res.sendFile(path.join(__dirname, '/meshViewer.js'));
//});

module.exports = router;
