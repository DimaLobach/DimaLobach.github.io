// create a stage
var stage = acgraph.create('stage-container');

// draw the frame
var frame = stage.rect(25, 50, 350, 300);

// draw the house
var walls = stage.rect(50, 250, 200, 100);
var roof  = stage.path()
  .moveTo(50, 250)
  .lineTo(150, 180)
  .lineTo(250, 250)
  .close();

// draw a man
var head = stage.circle(330, 280, 10);
var neck = stage.path().moveTo(330, 290).lineTo(330, 300);
var kilt = stage.triangleUp(330, 320, 20);
var rightLeg = stage.path().moveTo(320, 330).lineTo(320, 340);
var leftLeg = stage.path().moveTo(340, 330).lineTo(340, 340);

// color the picture
// fancy frame
frame.stroke(["red", "green", "blue"], 2, "2 2 2");
// brick walls
walls.fill(acgraph.hatchFill('horizontalbrick'));
// straw roof
roof.fill("#e4d96f");
// plaid kilt
kilt.fill(acgraph.hatchFill('plaid'));
