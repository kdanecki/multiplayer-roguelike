extends Dungeon


# Called when the node enters the scene tree for the first time.
func _ready():
	dungeon[1] = TILE_FOREST
	# print("test:", get_test())


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
