using System.Xml.Serialization;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class CrownInfo
    {
        [XmlAttribute]
        public int Id;
        public IW_ToothCoordinate ToothCoord;
        public IW_Curve toothProfile;
        public IW_Point3d AttachPosition;

        public CrownInfo()
        {
        }
    }
}
