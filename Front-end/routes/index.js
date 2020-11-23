var express = require('express');
var router = express.Router();
const path = require('path');
const testAddon = require('./../build/Release/testaddon.node');

/* GET welcome page. */
router.get('/meshmurammat', function(req, res, next) {
  res.sendFile(path.join(__dirname, '/welcome.html'));
});

/* GET home page. */

router.get('/home', function(req, res, next) {
  res.sendFile(path.join(__dirname, '/home.html'));
  //res.send(testAddon.hello());
});

router.get('/cpp', function(req, res, next) {
  
  res.send(testAddon.add(+req.query.a,+req.query.b).toString());
});

module.exports = router;
