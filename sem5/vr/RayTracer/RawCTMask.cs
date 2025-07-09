using System;
using System.IO;
using System.Text.RegularExpressions;

namespace rt;

public class RawCtMask : Geometry {
    private readonly Vector _position;
    private readonly double _scale;
    private readonly ColorMap _colorMap;
    private readonly byte[] _data;

    private readonly int[] _resolution = new int[3];
    private readonly double[] _thickness = new double[3];
    private readonly Vector _v0;
    private readonly Vector _v1;

    public RawCtMask(string datFile, string rawFile, Vector position, double scale, ColorMap colorMap) :
        base(Color.NONE) {
        _position = position;
        _scale = scale;
        _colorMap = colorMap;

        var lines = File.ReadLines(datFile);
        foreach (var line in lines) {
            var kv = Regex.Replace(line, "[:\\t ]+", ":").Split(":");
            if (kv[0] == "Resolution") {
                _resolution[0] = Convert.ToInt32(kv[1]);
                _resolution[1] = Convert.ToInt32(kv[2]);
                _resolution[2] = Convert.ToInt32(kv[3]);
            }
            else if (kv[0] == "SliceThickness") {
                _thickness[0] = Convert.ToDouble(kv[1]);
                _thickness[1] = Convert.ToDouble(kv[2]);
                _thickness[2] = Convert.ToDouble(kv[3]);
            }
        }

        _v0 = position;
        _v1 = position + new Vector(_resolution[0] * _thickness[0] * scale, _resolution[1] * _thickness[1] * scale,
            _resolution[2] * _thickness[2] * scale);

        var len = _resolution[0] * _resolution[1] * _resolution[2];
        _data = new byte[len];
        using FileStream f = new FileStream(rawFile, FileMode.Open, FileAccess.Read);
        if (f.Read(_data, 0, len) != len) {
            throw new InvalidDataException($"Failed to read the {len}-byte raw data");
        }
    }

    private ushort Value(int x, int y, int z) {
        if (x < 0 || y < 0 || z < 0 || x >= _resolution[0] || y >= _resolution[1] || z >= _resolution[2]) {
            return 0;
        }

        return _data[z * _resolution[1] * _resolution[0] + y * _resolution[0] + x];
    }

    private double[]? GetBoundingBoxIntersections(Line line) {
        var tMin = line.Dx.X >= 0 ? (_v0.X - line.X0.X) / line.Dx.X : (_v1.X - line.X0.X) / line.Dx.X;
        var tMax = line.Dx.X >= 0 ? (_v1.X - line.X0.X) / line.Dx.X : (_v0.X - line.X0.X) / line.Dx.X;

        var tyMin = line.Dx.Y >= 0 ? (_v0.Y - line.X0.Y) / line.Dx.Y : (_v1.Y - line.X0.Y) / line.Dx.Y;
        var tyMax = line.Dx.Y >= 0 ? (_v1.Y - line.X0.Y) / line.Dx.Y : (_v0.Y - line.X0.Y) / line.Dx.Y;

        if (tMin > tyMax || tyMin > tMax)
            return null;

        if (tyMin > tMin) tMin = tyMin;
        if (tyMax < tMax) tMax = tyMax;

        var tzMin = line.Dx.Z >= 0 ? (_v0.Z - line.X0.Z) / line.Dx.Z : (_v1.Z - line.X0.Z) / line.Dx.Z;
        var tzMax = line.Dx.Z >= 0 ? (_v1.Z - line.X0.Z) / line.Dx.Z : (_v0.Z - line.X0.Z) / line.Dx.Z;

        if (tMin > tzMax || tzMin > tMax)
            return null;

        if (tzMin > tMin) tMin = tzMin;
        if (tzMax < tMax) tMax = tzMax;

        if (tMin <= tMax)
            return new[] { tMin, tMax };
        return null;
    }

    public override Intersection GetIntersection(Line line, double minDist, double maxDist) {
        var ts = GetBoundingBoxIntersections(line);
        if (ts == null)
            return Intersection.NONE;
        var t1 = Math.Max(minDist, ts[0]);
        var t2 = Math.Min(maxDist, ts[1]);
        var curOpacity = 1d;
        var intersection = Intersection.NONE;
        for (var t = t1; t <= t2; t += _scale) {
            var curPoint = line.CoordinateToPosition(t);
            var curColor = GetColor(curPoint);
            if (curColor.Alpha == 0) continue;
            if (intersection.Color.Alpha == 0) {
                intersection = new Intersection
                (
                    true,
                    true,
                    this,
                    line,
                    t,
                    GetNormal(curPoint),
                    new Material(),
                    new Color()
                );
            }

            intersection.Color += curColor * curColor.Alpha * curOpacity;
            curOpacity *= 1 - curColor.Alpha;
            if (curOpacity < 1e-4) break;
        }

        intersection.Material = Material.FromColor(intersection.Color);
        return intersection;
    }

    private int[] GetIndexes(Vector v) {
        return new[] {
            (int)Math.Floor((v.X - _position.X) / _thickness[0] / _scale),
            (int)Math.Floor((v.Y - _position.Y) / _thickness[1] / _scale),
            (int)Math.Floor((v.Z - _position.Z) / _thickness[2] / _scale)
        };
    }

    private Color GetColor(Vector v) {
        int[] idx = GetIndexes(v);

        ushort value = Value(idx[0], idx[1], idx[2]);
        return _colorMap.GetColor(value);
    }

    private Vector GetNormal(Vector v) {
        int[] idx = GetIndexes(v);
        double x0 = Value(idx[0] - 1, idx[1], idx[2]);
        double x1 = Value(idx[0] + 1, idx[1], idx[2]);
        double y0 = Value(idx[0], idx[1] - 1, idx[2]);
        double y1 = Value(idx[0], idx[1] + 1, idx[2]);
        double z0 = Value(idx[0], idx[1], idx[2] - 1);
        double z1 = Value(idx[0], idx[1], idx[2] + 1);

        return new Vector(x1 - x0, y1 - y0, z1 - z0).Normalize();
    }
}