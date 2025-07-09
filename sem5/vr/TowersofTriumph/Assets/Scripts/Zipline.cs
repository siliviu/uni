using UnityEngine;

public class Zipline : MonoBehaviour
{
    [SerializeField] private Zipline targetZip;
    [SerializeField] private float zipSpeed = 250f;
    [SerializeField] private float zipScale = 0.2f;
    [SerializeField] private float arrivalTreshold = 1.75f;
    [SerializeField] private LineRenderer cable;
    
    public Transform ZipTransform;

    private bool zipping = false;
    private GameObject localZip;

    private void Awake()
    {
         cable.SetPosition(0, ZipTransform.position);
         cable.SetPosition(1, targetZip.ZipTransform.position);
    }

    // Update is called once per frame
    void Update()
    {
        if (!zipping || localZip == null) return;
        
        localZip.GetComponent<Rigidbody>().AddForce((targetZip.ZipTransform.position - ZipTransform.position).normalized * zipSpeed * Time.deltaTime, ForceMode.Acceleration);

        Debug.Log("Update");
        if (Vector3.Distance(localZip.transform.position, targetZip.ZipTransform.position) <= arrivalTreshold)
        {
            ResetZipline();
        }
    }

    public void StartZipline(GameObject player)
    {
        if (zipping) return;
        
        localZip = GameObject.CreatePrimitive(PrimitiveType.Sphere);
        localZip.transform.position = ZipTransform.position;
        // localZip.transform.localScale = new Vector3(zipScale, zipScale, zipScale);

        localZip.AddComponent<Rigidbody>().useGravity = false;
        localZip.GetComponent<Collider>().isTrigger = true;

        player.GetComponent<Rigidbody>().useGravity = false;

        player.GetComponent<PlayerMovement>().velocity = Vector3.zero;
        player.GetComponent<CharacterController>().enabled = false;
        player.GetComponent<PlayerMovement>().canMove = false;

        player.transform.SetParent(localZip.transform);
        player.transform.localPosition = new Vector3(0, player.transform.localPosition.y, 0);
        
        zipping = true;
    }

    private void ResetZipline()
    {
        if (!zipping) return;
        
        GameObject player = localZip.transform.GetChild(0).gameObject;
        player.GetComponent<Rigidbody>().useGravity = true;
        
        player.GetComponent<PlayerMovement>().velocity = Vector3.zero;
        player.GetComponent<CharacterController>().enabled = true;
        player.GetComponent<PlayerMovement>().canMove = true;

        player.transform.SetParent(null);
        Destroy(localZip);
        localZip = null;
        zipping = false;
        Debug.Log("Reset Zipline");
    }
}
