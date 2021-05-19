using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace DBTest
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            //Application.EnableVisualStyles();
            //Application.SetCompatibleTextRenderingDefault(false);
            //Application.Run(new Form1());
            DoThree();
            //DoFour();
            Console.ReadKey();
        }

        public static void DoOne()
        {
            DataSet2.ITEMDataTable table = new DataSet2.ITEMDataTable();
            table.AddITEMRow("001", "p102", "A", "no specific details");
            table.AddITEMRow("002", "p103", "B", "some details");
            StringWriter swr = new StringWriter();
            table.WriteXml(swr);
            Debug.WriteLine(swr.ToString());
        }

        public static void DoTwo()
        {
            Console.WriteLine("int \n MAX : {0} and MIN : {1} ", int.MaxValue, int.MinValue);
            Console.WriteLine("float \n MAX : {0} and MIN : {1} \n -ve infi : {2} +ve infi : {3}", float.MaxValue, float.MinValue, float.NegativeInfinity, float.PositiveInfinity);
            Console.WriteLine("double \n MAX : {0} and MIN : {1} \n NaN : {2} \n -ve infi : {3} +ve infi : {4}", double.MaxValue, double.MinValue, double.NaN, double.NegativeInfinity, double.PositiveInfinity);            
        }

        public static void DoThree()
        {
            DBTest.FinalStructure.TempDataSet.TempTableDataTable table = new DBTest.FinalStructure.TempDataSet.TempTableDataTable();
            table.AddTempTableRow(1, "p102", "A", 120.54f);
            table.AddTempTableRow(2, "p103", "B", 430.12f);
            StringWriter swr = new StringWriter();
            table.WriteXml(swr);
            Debug.WriteLine(swr.ToString());

            Console.WriteLine("========================");
            DBTest.FinalStructure.TempDataSet.TempTableDataTable dtable = new DBTest.FinalStructure.TempDataSet.TempTableDataTable();
            Console.WriteLine(dtable.Count);
            Console.WriteLine("");
            StringReader sreader = new StringReader(swr.ToString());
            dtable.ReadXml(sreader);
            Console.WriteLine(dtable.Count);
            Console.WriteLine("");    
        }

        public static void DoFour()
        {
            DBTest.FinalStructure2.TempDataSet.TempTableDataTable table = new DBTest.FinalStructure2.TempDataSet.TempTableDataTable();
            table.AddTempTableRow(1, "p102", "A", 120.54f);
            table.AddTempTableRow(2, "p103", "B", 430.12f);
            StringWriter swr = new StringWriter();
            table.WriteXml(swr);
            Debug.WriteLine(swr.ToString());

            Console.WriteLine("========================");
            DBTest.FinalStructure2.TempDataSet.TempTableDataTable dtable = new DBTest.FinalStructure2.TempDataSet.TempTableDataTable();
            Console.WriteLine(dtable.Count);
            Console.WriteLine("");
            StringReader sreader = new StringReader(swr.ToString());
            dtable.ReadXml(sreader);
            Console.WriteLine(dtable.Count);
            Console.WriteLine("");                        
        }
    }
}
