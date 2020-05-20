using System.Xml.Serialization;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class IW_Point3d
    {
        public IW_Point3d() { x = 0; y = 0; z = 0; }
        public IW_Point3d(double x, double y, double z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }
        [XmlAttribute]
        public double x;
        [XmlAttribute]
        public double y;
        [XmlAttribute]
        public double z;
    }
}
