using System.Xml.Serialization;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class IW_ToothFeature
    {
        [XmlAttribute]
        public int Id;

        public IW_Point3d Crown;
        public IW_Point3d Root;
        public IW_Point3d Mesial;
        public IW_Point3d Distal;
        public int state;
    }
}
