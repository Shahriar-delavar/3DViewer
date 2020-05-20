using System.IO;
using System.IO.Compression;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Xml.Serialization;
//http://blog.wahahajk.com/2009/06/c-serialize-binaryxml.html
namespace EZOrthoDataStructure
{
    //欄位要與CEZOrthoDoc 對應
    [System.Serializable]
    [XmlRootAttribute("EzDent-Ortho", Namespace = "http://www.inteware.com.tw", IsNullable = false)]
    public class ProjectDataWrapper
    {
        [XmlAttribute]
        public string File_Version = "v1.0.0";

        public string ver;//軟體版本

        public int workflowstep;

        public ProjectInstructionWP projectinstruction;

        public PatientInformationWP patientInformation;

        public PatientDiagnosisWP PatientDiagnosis;
     
        public IW_ToothFeature[] toothFeature;

        public IW_ToothCoordinate[] toothCoordinates;

        public IW_Curve[] FeaturePoints;

        public IW_Curve[] GumDeformFeature;

        public IW_TreatmentPlan plan;

        public TriMeshModels models;

        public IW_ToothCoordinate CephImageOrientation;
        public double CephW;
        public double CephH;

        public IW_ToothCoordinate ProfileImageOrientation;
        public double ProfileW;
        public double ProfileH;

        public IW_ToothCoordinate SmileImageOrientation;
        public double SmileW;
        public double SmileH;

        public IW_ToothCoordinate ArchwireAdjustmentMatrix;
        
        public IW_ToothCoordinate UpperModelMatrix;

        public IW_ToothCoordinate LowerModelMatrix;

        //public string ProductType;
        [XmlAttribute]
        public int ProductTypeEnum;

        public void CreateXML(string fp)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(ProjectDataWrapper));
            TextWriter writer = new StreamWriter(fp);
            serializer.Serialize(writer, this);
            writer.Close();
        }

        public void CreateBinary(string fp)
        {
            IFormatter binFmt = new BinaryFormatter();
            Stream s = File.Open(fp, FileMode.Create);
            binFmt.Serialize(s, this);
            s.Close();
        }

        static public ProjectDataWrapper ProjectDataWrapperDeserialize(string fp)
        {
            ProjectDataWrapper output;
            XmlSerializer serializer = new XmlSerializer(typeof(ProjectDataWrapper));
            using (Stream reader = new FileStream(fp, FileMode.Open))
            {
                // Call the Deserialize method to restore the object's state.
                output = (ProjectDataWrapper)serializer.Deserialize(reader);
            }
            return output;
        }

        static public ProjectDataWrapper ProjectDataWrapperDeserialize_Binary(string fp)
        {
            ProjectDataWrapper output;
            IFormatter binFmt = new BinaryFormatter();
            Stream s = File.Open(fp, FileMode.Open);
            output = (ProjectDataWrapper)binFmt.Deserialize(s);
            s.Close();
            return output;
        }
    }
}
