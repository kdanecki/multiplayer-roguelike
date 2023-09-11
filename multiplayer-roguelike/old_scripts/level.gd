extends Node2D

const SPAWN_RANDOM := 5.0

# Called when the node enters the scene tree for the first time.
func _ready():
	if not multiplayer.is_server():
		return
	multiplayer.peer_connected.connect(add_player)
	multiplayer.peer_disconnected.connect(del_player)
	
	for id in multiplayer.get_peers():
		add_player(id)
	
	if not OS.has_feature("dedicated server"):
		add_player(1)
	
func _exit_tree():
	if not multiplayer.is_server():
		return
	multiplayer.peer_connected.disconnect(add_player)
	multiplayer.peer_disconnected.disconnect(del_player)

func add_player(id: int):
	var character
	#if id == 1:
	character = preload("res://player.tscn").instantiate()
	#else:
	#	character = preload("res://goblin.tscn").instantiate()
	character.player = id
	var pos := Vector2.from_angle(randf() * 2 * PI)
	character.position = pos * randf() * SPAWN_RANDOM
	character.name = str(id)
	$Players.add_child(character, true)
	
func del_player(id: int):
	if not $Players.has_node(str(id)):
		return
	$Players.get_node(str(id)).queue_free()
