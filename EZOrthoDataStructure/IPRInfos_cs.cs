using System.Xml.Serialization;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class IPRInfos_CS
    {
        public IPRInfos_CS()
        {
            Id = -1;
            Adj_M = -1;
            Adj_D = -1;
            Value_M = 0.0f;
            Value_D = 0.0f;
            ClipNormal_M = new IW_Point3d();
            ClipNormal_D  = new IW_Point3d();
            ClipCenter_M  = new IW_Point3d();
            ClipCenter_D = new IW_Point3d();
        }

        [XmlAttribute]
        public int Id;
        public int Adj_M;
        public int Adj_D;
        public float Value_M;
        public float Value_D;
        public IW_Point3d ClipNormal_M;
        public IW_Point3d ClipNormal_D;
        public IW_Point3d ClipCenter_M;
        public IW_Point3d ClipCenter_D;
    }
}
