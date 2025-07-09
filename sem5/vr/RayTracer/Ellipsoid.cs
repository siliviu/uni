using System;


namespace rt {
    public class Ellipsoid : Geometry {
        private Vector Center { get; }
        private Vector SemiAxesLength { get; }
        private double Radius { get; }


        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Material material, Color color) : base(
            material, color) {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Color color) : base(color) {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        private Vector Normal(Vector point) {
            // gradient of equation = 0
            // 2 * (Xp-Xc) A
            // A =  1/a^2   0       0
            //      0       1/b^2   0
            //      0       0       1/c^2
            return (new Vector(
                    (point.X - Center.X) / (SemiAxesLength.X * SemiAxesLength.X),
                    (point.Y - Center.Y) / (SemiAxesLength.Y * SemiAxesLength.Y),
                    (point.Z - Center.Z) / (SemiAxesLength.Z * SemiAxesLength.Z))
                ).Normalize();
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist) {
            // (X-XC)T A (X-XC) = R^2
            // X=X0+DX t
            // At^2+Bt+C=0 where
            // A=DXT A DX
            // B=2(X0-XC)T A DX
            // C=(X0-XC)T A (X0-XC) - R^2
            Vector a = new Vector(line.Dx.X / SemiAxesLength.X, line.Dx.Y / SemiAxesLength.Y,
                line.Dx.Z / SemiAxesLength.Z);
            Vector c = new Vector((line.X0.X - Center.X) / SemiAxesLength.X, (line.X0.Y - Center.Y) / SemiAxesLength.Y,
                (line.X0.Z - Center.Z) / SemiAxesLength.Z);
            var A = a.Length2();
            var B = 2 * (a * c);
            var C = c.Length2() - Radius * Radius;
            var D = B * B - 4 * A * C;
            if (D >= 0) {
                var T = (-B - double.Sqrt(D)) / (2 * A);
                if (T >= minDist && T <= maxDist) {
                    var X = line.CoordinateToPosition(T);
                    return new Intersection(true, true, this, line, T, Normal(X), Material, Color);
                }
            }

            return Intersection.NONE;
        }
    }
}