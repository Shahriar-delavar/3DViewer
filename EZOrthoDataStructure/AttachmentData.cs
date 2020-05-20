using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Xml.Serialization;

namespace EZOrthoDataStructure
{
    [System.Serializable]
    public class AttachmentData
    {
        public string ItemName { get; set; }
        public string ItemType { get; set; }
        public int ItemWidth { get; set; }
        public int ItemHeight { get; set; }
        public string ItemId { get; set; }
        public byte[] ThumbnailImg { get; set; }//縮圖資料
        public byte[] ModelData { get; set; }

        [XmlIgnoreAttribute]
        public string FilePath { get; set; }

        //https://dotblogs.com.tw/atowngit/2010/01/12/12972
        public void SetImageData(System.Drawing.Bitmap BmpImg)
        {
            if (BmpImg == null) { return; }
            byte[] data = null;
            using (MemoryStream oMemoryStream = new MemoryStream())
            {
                //建立副本
                using (Bitmap oBitmap = new Bitmap(BmpImg))
                {
                    //儲存圖片到 MemoryStream 物件，並且指定儲存影像之格式
                    oBitmap.Save(oMemoryStream, ImageFormat.Bmp);
                    //設定資料流位置
                    oMemoryStream.Position = 0;
                    //設定 buffer 長度
                    data = new byte[oMemoryStream.Length];
                    //將資料寫入 buffer
                    oMemoryStream.Read(data, 0, Convert.ToInt32(oMemoryStream.Length));
                    //將所有緩衝區的資料寫入資料流
                    oMemoryStream.Flush();
                }
            }
            ThumbnailImg = data;
        }

        public void Serialize(string fp)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(AttachmentData));
            TextWriter writer = new StreamWriter(fp);
            serializer.Serialize(writer, this);
            writer.Close();
        }
        static public AttachmentData Deserialize(string fp)
        {
            AttachmentData output = new AttachmentData();
            XmlSerializer serializer = new XmlSerializer(typeof(AttachmentData));
            using (Stream reader = new FileStream(fp, FileMode.Open))
            {
                // Call the Deserialize method to restore the object's state.
                output = (AttachmentData)serializer.Deserialize(reader);
            }
            return output;
        }
    }
}
