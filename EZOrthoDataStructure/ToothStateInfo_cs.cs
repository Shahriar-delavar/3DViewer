using System.Xml.Serialization;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class ToothStateInfo_CS
    {
        public ToothStateInfo_CS()
        {
            Id = -1;
            ExtractFrom = -1;
            Is_Fix = false;
            Is_Lack = false;
        }
        [XmlAttribute]
        public int Id;
        public int ExtractFrom;//
        public bool Is_Fix;
        public bool Is_Lack;
    }
}
