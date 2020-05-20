using System.Xml.Serialization;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class TreatmentStep//同 StepPlan
    {
        public TreatmentStep() { }

        [XmlAttribute]
        public string OutputTime;
        public MovementInfo[] MoveInfos;//16個
    }
}
