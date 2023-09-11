extends MultiplayerSynchronizer

@export var move_direction := Vector2()
@export var attack_direction := Vector2()
#@export var action := CharacterBase.ACTION_NONE

# Called when the node enters the scene tree for the first time.
func _ready():
	set_process(get_multiplayer_authority() == multiplayer.get_unique_id())


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	attack_direction = (get_parent().get_global_mouse_position() - get_parent().position)
	move_direction = Input.get_vector("ui_left", "ui_right", "ui_up", "ui_down")
	#print(Vector2.from_angle(PI/6).length())
	if Input.is_action_pressed("move_up"):
		#move_direction = -PI/2
		#print(-PI/2)
		move_direction.y -= 1
	if Input.is_action_pressed("move_right_up"):
		#move_direction = -PI/6 - 0.01
		#print(-PI/6)
		move_direction += Vector2(3, -2)
	if Input.is_action_pressed("move_right_down"):
		#move_direction = PI/6
		move_direction += Vector2(3, 2)
	if Input.is_action_pressed("move_down"):
		#move_direction = PI/2
		move_direction.y += 1
	if Input.is_action_pressed("move_left_up"):
		#move_direction = PI + PI/6
		move_direction += Vector2(-3, -2)
	if Input.is_action_pressed("move_left_down"):
		#move_direction = PI - PI/6
		move_direction += Vector2(-3, 2)
#	if Input.is_action_pressed("attack"):
	#	action = CharacterBase.ACTION_ATTACK
#	else:
#		action = CharacterBase.ACTION_NONE
	
	# print(move_direction)
