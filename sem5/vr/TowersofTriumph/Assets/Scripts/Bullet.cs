using UnityEngine;

public class Bullet : MonoBehaviour {
	private void OnCollisionEnter(Collision other) {
		if (other.gameObject.CompareTag("Target")) {
			other.gameObject.GetComponent<Rigidbody>().isKinematic = false;
		}
	}
}
