using System.Xml.Serialization;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class IW_ToothCoordinate
    {
        [XmlAttribute]
        public int Id;

        public double[] Mv = new double[16];
    }
}
