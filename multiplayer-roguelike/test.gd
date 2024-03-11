extends MultiplayerSynchronizer


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

var timer = 3
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	timer -= delta
	if timer < 0:
		var a = 1
		for i in range(0, 100000):
			a += sqrt(i * a + 123)
		timer = 3
	
