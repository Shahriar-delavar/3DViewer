namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class TreatmentSetup//同 SetupPlan
    {
        public string TreatmentName;
        public JawSetupPlan_CS UpperPlan;
        public JawSetupPlan_CS LowerPlan;
        public ToothStateInfo_CS[] ToothStates;
    }
}
