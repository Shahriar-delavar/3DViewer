using System.Xml.Serialization;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class IW_TreatmentPlan
    {
        public IW_TreatmentPlan() { }
        [XmlAttribute]
        public int BestPlan;
        public TreatmentSetup[] treatmentSetup;
    }
}
