// create stage
var stage = acgraph.create("stage-container");

// color palettes for leaves
var palette_fill = ['#5f8c3f', '#cb9226', '#515523', '#f2ad33', '#8b0f01']; 
var palette_stroke = ['#43622c', '#8e661b', '#393b19', '#a97924', '#610b01'];

// counter
var leavesCounter = 0;

// create a label to count leaves
var counterLabel = stage.text(10,10, "Swiped: 0", {fontSize: 20});

// a layer for the leaves
var gameLayer = stage.layer().zIndex(counterLabel.zIndex()-1);

function drawLeaf(x, y) {
  // choose a random color from a palette
  var index = Math.floor(Math.random() * 5);
  var fill = palette_fill[index];
  var stroke = palette_stroke[index];

  // generate random scaling factor and rotation angle
  var scale = Math.round(Math.random() * 30) / 10 + 1;
  var angle = Math.round(Math.random() * 360 * 100) / 100;

  // create a new path (leaf)
  var path = acgraph.path();

  // color and draw a leaf
  path.fill(fill).stroke(stroke, 1, 'none', 'round', 'round');
  var size = 18;
  path.moveTo(x, y)
    .curveTo(x + size / 2, y - size / 2, x + 3 * size / 4, y + size / 4, x + size, y)                  
    .curveTo(x + 3 * size / 4, y + size / 3, x + size / 3, y + size / 3, x, y);

  // apply random transformations
  path.scale(scale, scale, x, y).rotate(angle, x, y);

  path.listen("mouseover", function(){
    path.remove();
    counterLabel.text("Swiped: " + leavesCounter++);
    if (gameLayer.numChildren() < 200) shakeTree(300); 
  });

  return path; 
};

function shakeTree(n){
  stage.suspend(); // suspend rendering
  for (var i = 0; i < n; i++) {
    var x = Math.random() * stage.width()/2 + 50;
    var y = Math.random() * stage.height()/2 + 50;
    gameLayer.addChild(drawLeaf(x, y)); // add a leaf
  }

  stage.resume(); // resume rendering
}

// shake a tree for the first time
shakeTree(500);
