using System.Xml.Serialization;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class IW_Curve
    {
        [XmlAttribute]
        public int Id;
        public IW_Point3d[] pts;
    }
}
