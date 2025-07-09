using UnityEngine;

public class Gun : MonoBehaviour
{
    public Camera cam;
    
    public Transform bulletSpawnPoint;
    public GameObject bulletPrefab;
    public float bulletSpeed = 10;
    public float upwardForce = 0;

    private LineRenderer lineRenderer;

    private void Start()
    {
        lineRenderer = gameObject.AddComponent<LineRenderer>();
        lineRenderer.startWidth = 0.1f;
        lineRenderer.endWidth = 0.1f;
        lineRenderer.material = new Material(Shader.Find("Sprites/Default"));
        lineRenderer.startColor = Color.red;
        lineRenderer.endColor = Color.red;
    }


    // Update is called once per frame
    void Update()
    {
        if (Input.GetButtonDown("Fire1"))
        {
            Ray ray = new Ray(cam.transform.position, cam.transform.forward);
            RaycastHit hit;

            Vector3 targetPoint;
            if (Physics.Raycast(ray, out hit))
            {
                Debug.Log(hit.collider.tag);
                targetPoint = hit.point;
                // .CompareTag("Target")
            }
            else
            {
                targetPoint = ray.GetPoint(75);
            }

            Vector3 direction = targetPoint - bulletSpawnPoint.position;
            
            Debug.DrawRay(bulletSpawnPoint.position, direction, Color.green);
            
            var bullet = Instantiate(bulletPrefab, bulletSpawnPoint.position, bulletSpawnPoint.rotation);
            bullet.transform.forward = direction.normalized;
            
            bullet.GetComponent<Rigidbody>().AddForce(direction.normalized * bulletSpeed, ForceMode.Impulse);
            bullet.GetComponent<Rigidbody>().AddForce(cam.transform.up * upwardForce, ForceMode.Impulse);
            
            Destroy(bullet, 10);
        }
        
    }
}
