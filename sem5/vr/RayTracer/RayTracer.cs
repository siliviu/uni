using System;

namespace rt {
    class RayTracer {
        private Geometry[] geometries;
        private Light[] lights;

        public RayTracer(Geometry[] geometries, Light[] lights) {
            this.geometries = geometries;
            this.lights = lights;
        }

        private double ImageToViewPlane(int n, int imgSize, double viewPlaneSize) {
            return -n * viewPlaneSize / imgSize + viewPlaneSize / 2;
        }

        private Intersection FindFirstIntersection(Line ray, double minDist, double maxDist, bool lightning = false) {
            var intersection = Intersection.NONE;

            foreach (var geometry in geometries)
                if (!lightning || geometry is not RawCtMask) {
                    var intr = geometry.GetIntersection(ray, minDist, maxDist);

                    if (!intr.Valid || !intr.Visible) continue;

                    if (!intersection.Valid || !intersection.Visible) {
                        intersection = intr;
                    }
                    else if (intr.T < intersection.T) {
                        intersection = intr;
                    }
                }

            return intersection;
        }

        private bool IsLit(Vector point, Light light) {
            if (FindFirstIntersection(new Line(light.Position, point),
                    0, (point - light.Position).Length() - 1e-2, true).Valid)
                return false;
            return true;
        }

        public void Render(Camera camera, int width, int height, string filename) {
            var background = new Color(0.2, 0.2, 0.2, 1.0);
            var image = new Image(width, height);
            for (var i = 0; i < width; i++) {
                for (var j = 0; j < height; j++) {
                    var planePoint =
                        camera.Position + camera.Direction * camera.ViewPlaneDistance +
                        camera.Up * ImageToViewPlane(j, height, camera.ViewPlaneHeight) +
                        (camera.Up ^ camera.Direction) * ImageToViewPlane(i, width, camera.ViewPlaneWidth);
                    var ray = new Line(camera.Position, planePoint);
                    var intersection = FindFirstIntersection(ray,
                        camera.FrontPlaneDistance, camera.BackPlaneDistance);
                    if (!intersection.Valid) {
                        image.SetPixel(i, j, background);
                        continue;
                    }

                    var eyeIntersection = (camera.Position - intersection.Position).Normalize();
                    // var eyeIntersection = (camera.Position - planePoint).Normalize(); // ALTERNATE
                    var color = new Color();
                    var material = intersection.Material;
                    foreach (var light in lights) {
                        color += material.Ambient * light.Ambient * light.Intensity;
                        if (IsLit(intersection.Position, light)) {
                            var lightIntersection = (light.Position - intersection.Position).Normalize();
                            var reflection = (intersection.Normal * (intersection.Normal * lightIntersection) * 2 -
                                              lightIntersection)
                                .Normalize();
                            color += (material.Diffuse * light.Diffuse
                                                       * Math.Max(0, lightIntersection * intersection.Normal) +
                                      material.Specular * light.Specular
                                                        * Math.Pow(Math.Max(eyeIntersection * reflection, 0),
                                                            material.Shininess)
                                ) * light.Intensity;
                        }
                    }

                    image.SetPixel(i, j, color);
                }
            }

            image.Store(filename);
        }
    }
}