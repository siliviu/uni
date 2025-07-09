using UnityEngine;

public class PlayerMovement : MonoBehaviour {
	public CharacterController controller;

	public bool canMove = true;

	public float speed = 12f;
	public float gravity = -9.81f * 2;
	public float jumpHeight = 3f;

	public Transform groundCheck;
	public float groundDistance = 0.4f;
	public LayerMask groundMask;

	private float checkOffset = 1f;
	private float checkRadius = 2f;

	public Vector3 velocity;

	bool isGrounded;

	// Update is called once per frame
	void Update() {


		if (Input.GetKeyDown(KeyCode.E)) {
			RaycastHit[] hits = Physics.SphereCastAll(transform.position + new Vector3(0, checkOffset, 0), checkRadius, Vector3.up);
			foreach (var hit in hits) {
				if (hit.collider.CompareTag("Zipline")) {
					Debug.Log(hit.collider.name);
					hit.collider.GetComponent<Zipline>().StartZipline(gameObject);
				}
			}
		}

		if (!canMove) return;

		//checking if we hit the ground to reset our falling velocity, otherwise we will fall faster the next time
		isGrounded = Physics.CheckSphere(groundCheck.position, groundDistance, groundMask);
		if (isGrounded && velocity.y < 0) {
			velocity.y = -2f;
		}

		float x = Input.GetAxis("Horizontal");
		float z = Input.GetAxis("Vertical");

		//right is the red Axis, foward is the blue axis
		Vector3 move = transform.right * x + transform.forward * z;

		controller.Move(move * speed * Time.deltaTime);

		//check if the player is on the ground so he can jump
		if (Input.GetButtonDown("Jump") && isGrounded) {
			//the equation for jumping
			velocity.y = Mathf.Sqrt(jumpHeight * -2f * gravity);
		}

		velocity.y += gravity * Time.deltaTime;

		controller.Move(velocity * Time.deltaTime);
	}
}