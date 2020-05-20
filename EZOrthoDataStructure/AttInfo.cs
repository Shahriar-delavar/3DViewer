namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class AttInfo//同AttachmentInfo
    {
        public AttInfo() { }
        public double[] OriginalM = new double[16];
        public double[] AdjustM = new double[16];
        public double[] AdjustM_Scale = new double[16];
        public string AttachName;
        public int AttachedToothIdx;
    }
}
