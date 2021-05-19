using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MangdWrapper_FirebirdDDFProvider;
using MangdTypes_FirebirdDDFProvider;
using System.Diagnostics;

namespace SimpleCSharpClient
{
    class Program
    {
        static void Main(string[] args)
        {
            MangdWrapper_FirebirdDDFProvider.FirebirdDDFProviderWrapper wrapper = new FirebirdDDFProviderWrapper();
            //FbDBHandle handle  = new FbDBHandle("localhost", "D:\\WORK\\first_test_project\\PurchaseOrderProjectSept_1 (1)\\EASYPO.FDB", "SYSDBA", "masterkey");
            FbDBHandle handle = wrapper.GetDDFProviderHandle("localhost", "D:\\WORK\\first_test_project\\PurchaseOrderProjectSept_1 (1)\\EASYPO.FDB", "SYSDBA", "masterkey");
            //FbDBHandle handle = wrapper.GetDDFProviderHandle("localhost", "D:\\Database\\gpser.gdb", "SYSDBA", "masterkey");
            List<string> list = wrapper.GetAllTablesForDatabase(handle);
            Console.WriteLine("Table count : " + list.Count);
            Console.WriteLine("List of tables : ");            
            //foreach (var item in list)
            //{                
            //    Console.WriteLine(item);
            //}

            List<Managed_TableColumnInfo> fld_info_list = wrapper.GetColumnInfoForTable(handle, "LOGIN");
            foreach(var fld_info in fld_info_list)
            {
                Debug.WriteLine("---------------------------");
                Debug.WriteLine("Fld name : " + fld_info.ColumnName);
                Debug.WriteLine("Fld type : " + fld_info.DataType.ToString());
                Debug.WriteLine("Fld length : " + fld_info.FieldLength);
                Debug.WriteLine("Fld has auto-incr : " + fld_info.IsAutoIncrement);
                Debug.WriteLine("Fld is unique : " + fld_info.IsUniqueField.ToString());
                Debug.WriteLine("Fld const type : " + fld_info.ConstraintType.ToString());
                Debug.WriteLine("Is not null col : "+ fld_info.IsNotNull.ToString());
                Debug.WriteLine("---------------------------");
            }
            var x = Console.ReadKey();            
        }
    }
}
