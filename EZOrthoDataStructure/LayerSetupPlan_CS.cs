using System.Xml.Serialization;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class LayerSetupPlan_CS
    {
        public LayerSetupPlan_CS()
        {
            InterType = -1;
            InterStep = 0;
            InterDist = 0;
            InterIE = 0;
            InterAng = 0;
        }
        [XmlAttribute]
        public string LayerName;

        public IPRInfos_CS[] IPRs;
        public AttInfo[] Atts;
        public TreatmentStep Goal;
        public TreatmentStep[] Steps;

        public int InterType;
        public float InterStep;
        public float InterDist;
        public float InterIE;
        public float InterAng;
    }
}
