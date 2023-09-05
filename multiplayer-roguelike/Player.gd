extends PlayerBase

@export var player := 1 :
	set(id):
		player = id
		$InputSynchronizer.set_multiplayer_authority(id)

@onready var input = $InputSynchronizer

func _ready():
	if player == multiplayer.get_unique_id():
		$Camera2D.make_current()

func _process(delta):
	# print(direction)
	direction = input.direction
	process(delta)
	# super(delta)
#	if direction:
#		velocity = direction.normalized() * 300
#	else:
#		velocity.x = move_toward(velocity.x, 0, 300)
#		velocity.y = move_toward(velocity.y, 0, 300)
#
#	move_and_slide()
	#print(direction)
	#print(typeof(input))

#func _ready():
	#if player == multiplayer.get_unique_id():
	#	$Camera2D.make_current()

#const SPEED = 300.0
#const JUMP_VELOCITY = -400.0

# Get the gravity from the project settings to be synced with RigidBody nodes.
#var gravity = ProjectSettings.get_setting("physics/2d/default_gravity")


#func _physics_process(delta):
#	# Add the gravity.
#	#if not is_on_floor():
#	#	velocity.y += gravity * delta
#
#	# Handle Jump.
#	#if Input.is_action_just_pressed("ui_accept") and is_on_floor():
#	#	velocity.y = JUMP_VELOCITY
#
#	# Get the input direction and handle the movement/deceleration.
#	# As good practice, you should replace UI actions with custom gameplay actions.
#	var direction = Input.get_vector("ui_left", "ui_right", "ui_up", "ui_down")
#	if direction:
#		velocity.x = direction.x * SPEED
#		velocity.y = direction.y * SPEED
#	else:
#		velocity.x = move_toward(velocity.x, 0, SPEED)
#		velocity.y = move_toward(velocity.y, 0, SPEED)
#
#	move_and_slide()
