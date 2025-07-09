using UnityEngine;

public class WreckingBallController : MonoBehaviour {
	public Rigidbody stopper;
	public Rigidbody support;
	public Rigidbody wall;
	public Transform player;
	private bool destroyed = false;

	// Start is called once before the first execution of Update after the MonoBehaviour is created
	void Start() {
	}

	// Update is called once per frame
	void Update() {
		if ((!stopper.isKinematic || !support.isKinematic) && !destroyed) {
			destroyed = true;
			stopper.isKinematic = false;
			support.isKinematic = false;
			wall.isKinematic = false;
		}
		bool shouldHaveWeapon = Vector3.Distance(player.position, stopper.position) <= 25f;
		Debug.Log(shouldHaveWeapon);
		player.GetChild(2).gameObject.SetActive(shouldHaveWeapon);

	}
}
