using System.Xml.Serialization;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class MovementInfo//同ToothMovement
    {
        public MovementInfo()
        {
            Id = -1;
        }
        [XmlAttribute]
        public int Id;
        public double[] Mv = new double[16];//setupM
        //public bool is_extract;
        //public bool is_fix;
    }
}
