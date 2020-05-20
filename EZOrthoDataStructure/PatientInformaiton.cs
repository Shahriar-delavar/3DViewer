using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class PatientInformationWP
    {
        public PatientInformationWP()
        {
            m_PatientID = "";   //病例編號
            m_PatientName = ""; //患者姓名
            m_PatientPhone = ""; //患者Phone
            m_PatientSex = true; // 0 female; 1 male
            m_PatientBday = "";
            m_PatientAddress = ""; //患者住址

            m_DentistName = ""; //醫師姓名
            m_ClinicName = ""; //診所名稱

            m_LabName = "";//牙技姓名
            m_LabWorkerName = "";//牙技所名稱

            m_Discribe = "";//建立資料時的備註
            m_CreateTime = "";//輸入年月日

        }

        public string m_PatientID;   //病例編號
        public string m_PatientName; //患者姓名
        public string m_PatientPhone; //患者Phone
        public bool m_PatientSex; // 0 female; 1 male
        public string m_PatientBday;
        public string m_PatientAddress; //患者住址

        public string m_DentistName; //醫師姓名
        public string m_ClinicName; //診所名稱

        public string m_LabName;//牙技姓名
        public string m_LabWorkerName;//牙技所名稱

        public string m_Discribe;//建立資料時的備註
        public string m_CreateTime;//輸入年月日_hhmmss
    }
}
