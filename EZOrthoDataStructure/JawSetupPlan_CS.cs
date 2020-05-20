using System.Xml.Serialization;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class JawSetupPlan_CS
    {
        [XmlAttribute]
        public bool isUp;
        public LayerSetupPlan_CS[] Layers;
    }
}
