extends Dungeon

var timer = 1

#@export
#var dungeon :Array[int] = []
# var size = Vector2i(10, 10)

func visibility_bla():
	print("visibility")

@rpc("authority")
func refresh(p_dungeon):
	print("refresh")
	dungeon = p_dungeon
	for tile in dungeon:
		#print(Vector2i((i % 10) - 5, (i / 10) - 5))
		set_cell(0, tile, 0, Vector2i(dungeon[tile], 0))

func refresh_peer(id :int):
	rpc_id(id, "refresh", dungeon)

# Called when the node enters the scene tree for the first time.
func _ready():
	if multiplayer.is_server():
		generate()
		multiplayer.peer_connected.connect(refresh_peer)
		refresh(dungeon)
		#for i in get_used_cells(0):
		#	print(get_cell_atlas_coords(0, i))

@rpc("authority", "call_local")
func update_tile(pos : Vector2i, type :Vector2i):
	# dungeon[(pos.y+5)*10 + pos.x + 5] = TileType.YELLOW_GRASS
	set_cell(0, pos, 0, type)

#var bla = 0
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
#	if multiplayer.is_server():
#		timer -= delta
#		if timer <= 0:
#			var pos = Vector2i(-bla, 0)# Vector2i(randi_range(-5, 4), randi_range(-5, 4))
#			var type = Vector2i(1, 0)
#			rpc("update_tile", pos, type)
#			pos = Vector2i(0, -bla)
#			type = Vector2i(2, 0)
#			rpc("update_tile", pos, type)
#			pos = Vector2i(-bla, bla)
#			type = Vector2i(3, 0)
#			rpc("update_tile", pos, type)
#			# set_cell(0, Vector2i(randi_range(-5, 5), randi_range(-5, 5)), 3, Vector2i(1, 0))
#			timer = 0.5
#			bla+=1
