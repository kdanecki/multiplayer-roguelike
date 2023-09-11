extends CharacterBase

#@export var player := 1 :
#	set(id):
#		player = id
#		$InputSynchronizer.set_multiplayer_authority(id)
#
#@onready var input = $InputSynchronizer
#
#var target = null
#var range := 70.0
#var dead = false
#
#func _ready():
#	if player == multiplayer.get_unique_id():
#		$Camera2D.make_current()
#
#func _physics_process(_delta):
#	physics_process(_delta)
#	var space_state = get_world_2d().direct_space_state
#
#	var query = PhysicsRayQueryParameters2D.create(position, position + attack_direction*range)
#	var result = space_state.intersect_ray(query)
#	if result:
#		target = result.collider
#	else:
#		target = null
#
#func _draw():
#	#draw_line(Vector2(0, 100), Vector2(500, 200), Color.RED, 10)
#	draw_line(Vector2(0, 0), attack_direction*range, Color.RED, 10)
#
#func _process(delta):
#	# print(direction)
#	#print($AnimatedSprite2D.sprite_frames.get_frame_count($AnimatedSprite2D.get_animation()))
#	#queue_redraw()
#	if Input.is_action_just_pressed("ui_accept"):
#		$AnimatedSprite2D.play("idle")
#
#	attack_direction = input.attack_direction.normalized()
#	move_direction = input.move_direction
#	action = input.action
#	$AnimatedSprite2D.position = Vector2(0, 0)
#	if !dead:
#		if action == ACTION_ATTACK:
#			var progress = ($AnimatedSprite2D.frame + $AnimatedSprite2D.frame_progress) / $AnimatedSprite2D.sprite_frames.get_frame_count($AnimatedSprite2D.get_animation())
#			if progress > 0.5:
#				$AnimatedSprite2D.position = lerp(attack_direction*30, Vector2(0, 0), (progress - 0.5)*2)
#			else:
#				$AnimatedSprite2D.position = lerp(Vector2(0, 0), attack_direction*30, progress * 2)
#			if attack_direction.x < 0:
#				$AnimatedSprite2D.flip_h = true
#			else:
#				$AnimatedSprite2D.flip_h = false
#			if $AnimatedSprite2D.get_animation() != "attack" and $AnimatedSprite2D.get_animation() != "attack2":
#				if randi_range(0, 1):
#					$AnimatedSprite2D.play("attack")
#				else:
#					$AnimatedSprite2D.play("attack2")
#		elif move_direction.length_squared() > 0:
#			$AnimatedSprite2D.play("run")
#			if move_direction.x < 0:
#				$AnimatedSprite2D.flip_h = true
#			else:
#				$AnimatedSprite2D.flip_h = false
#		else:
#			$AnimatedSprite2D.play("stay")
#		process(delta)
#
#func animation_finished():
#	if !dead:
#		$AnimatedSprite2D.play("stay")
#
#func attack():
#	if ($AnimatedSprite2D.get_animation() == "attack" and $AnimatedSprite2D.frame == 1) or ($AnimatedSprite2D.get_animation() == "attack2" and $AnimatedSprite2D.frame == 1):
#		var hit = target as CharacterBase
#		if hit:
#			hit.damage(5)
#			#print("slash", target)
#		else:
#			print("bash")
#
#func damage(amount : int):
#	health -= amount
#	if health <= 0 and not dead:
#		dead = true
#		$AnimatedSprite2D.play("die")

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
