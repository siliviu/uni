using UnityEngine;

public class Scroll : MonoBehaviour {

	public Transform player;
	public Transform segment1; // Top fixed segment
	public Transform segment2; // Second segment (rotates around Segment1)
	public Transform segment3; // Second segment (rotates around Segment1)
	public Transform segment4; // Second segment (rotates around Segment1)
							   //public Transform segment3; // Third segment (rotates around Segment2)
	private bool start = false;
	public float targetAngle = 0;
	public float actvitationDistance = 12f;
	public float unfoldSpeed1 = 100f;
	public float unfoldSpeed2 = 200f;
	public float unfoldSpeed3 = 400f;
	public float unfoldSpeed4 = 800f;
	public float epsilon = 1e-2f;
	void Start() {
	}
	float normalizeAngle(float angle) {
		if (angle > 180) {
			angle -= 360;
		}
		return angle;
	}
	void Update() {
		if (!start && Input.GetKey(KeyCode.E) && Vector3.Distance(player.position,segment1.position) <= actvitationDistance) {
			start = true;
		}
		if (!start)
			return;
		if (targetAngle - normalizeAngle(segment1.eulerAngles.z) > epsilon) {
			float difference = Mathf.Min(unfoldSpeed1 * Time.deltaTime, targetAngle - normalizeAngle(segment1.eulerAngles.z));
			segment1.Rotate(Vector3.forward, difference);
			return;
		}
		if (targetAngle - normalizeAngle(segment2.eulerAngles.z) > epsilon) {
			float difference = Mathf.Min(unfoldSpeed2 * Time.deltaTime, targetAngle - normalizeAngle(segment2.eulerAngles.z));
			segment2.Rotate(Vector3.forward, difference);
			return;
		}
		if (targetAngle - normalizeAngle(segment3.eulerAngles.z) > epsilon) {
			float difference = Mathf.Min(unfoldSpeed3 * Time.deltaTime, targetAngle - normalizeAngle(segment3.eulerAngles.z));
			segment3.Rotate(Vector3.forward, difference);
			return;
		}
		if (targetAngle - normalizeAngle(segment4.eulerAngles.z) > epsilon) {
			float difference = Mathf.Min(unfoldSpeed4 * Time.deltaTime, targetAngle - normalizeAngle(segment4.eulerAngles.z));
			segment4.Rotate(Vector3.forward, difference);
			return;
		}
	}
}
