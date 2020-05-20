namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class PatientDiagnosisWP
    {
        public PatientDiagnosisWP()
        {
            Crowding = false;
            Spacing = false;
            ClassII1 = false;
            ClassII2 = false;
            ClassIII = false;
            OpenBite = false;
            AnteriorCrossBite = false;
            PosteriorCrossBite = false;
            AnteriorOverbite = false;
            TaperingArch = false;
            OverJet = false;
            AnteriorOverjet = false;
            FixSmileingArc = false;
            DistortedTeeth = false;
            Instruction = "";
            Instruction_feature = "";
            Instruction_problem = "";
            Instruction_target = "";
            Instruction_plan = "";
        }

        public bool Crowding;
        public bool Spacing;
        public bool ClassII1;
        public bool ClassII2;
        public bool ClassIII;
        public bool OpenBite;
        public bool AnteriorCrossBite;
        public bool PosteriorCrossBite;
        public bool AnteriorOverbite;
        public bool TaperingArch;
        public bool OverJet;
        public bool AnteriorOverjet;
        public bool FixSmileingArc;
        public bool DistortedTeeth;
        public string Instruction;

        public string Instruction_feature;
        public string Instruction_problem;
        public string Instruction_target;
        public string Instruction_plan;
    }
}
