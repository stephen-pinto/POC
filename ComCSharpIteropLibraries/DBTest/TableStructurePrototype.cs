//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;

namespace DBTest
{
    ////Following defines table
    //[System.Serializable()]
    //class TempTableDataTable : global::System.Data.TypedTableBase<TempTableDataRow>
    //{
    //    public TempTableDataTable()
    //    {
    //        this.TableName = "TempTable";
    //        this.BeginInit();
    //        this.EndInit();
         
    //    }

    //    public TempTableDataRow AddTempTableRow(int COLUMN_ONE, string COLUMN_TWO, string COLUMN_THREE)
    //    {
    //        TempTableDataRow newRow = (TempTableDataRow) this.NewRow();
    //        object[] columnValuesArray = new object[]{
    //            COLUMN_ONE,
    //            COLUMN_TWO,
    //            COLUMN_THREE};
    //        this.Rows.Add(newRow);
    //        return newRow;
    //    }
    //}

    ////Following defines rows
    //[System.Serializable()]
    //class TempTableDataRow : System.Data.DataRow
    //{
    //    [System.Xml.Serialization.XmlElement("COLUMN_ONE")]
    //    public DataColumnExtTyped<int> objCOLUMN_ONE;
    //    [System.Xml.Serialization.XmlElement("COLUMN_TWO")]
    //    public DataColumnExtTyped<string> objCOLUMN_TWO;
    //    [System.Xml.Serialization.XmlElement("COLUMN_THREE")]
    //    public DataColumnExtTyped<string> objCOLUMN_THREE;

    //    public TempTableDataRow(System.Data.DataRowBuilder builder) : 
    //        base(builder)
    //    {
    //        objCOLUMN_ONE = new DataColumnExtTyped<int>("COLUMN_ONE", null);

    //        objCOLUMN_TWO = new DataColumnExtTyped<string>("COLUMN_TWO", null);
    //        objCOLUMN_TWO.MaxLength = 20;

    //        objCOLUMN_THREE = new DataColumnExtTyped<string>("COLUMN_THREE", null);
    //        objCOLUMN_THREE.MaxLength = 50;
    //    }

    //    public override object this[System.Data.DataColumn col]
    //    {
    //        get
    //        {
    //            return ((DataColumnExt)col).DataValueExt;
    //        }
    //        set
    //        {
    //            ((DataColumnExt)col).DataValueExt = value;
    //        }
    //    }        

    //    public int COLUMN_ONE
    //    {
    //        get
    //        {
    //            try
    //            {
    //                return this.objCOLUMN_ONE.DataValueTypedExt;
    //            }
    //            catch(System.Exception exp)
    //            {
    //                throw exp;
    //            }
    //        }
    //        set
    //        {
    //            this.objCOLUMN_ONE.DataValueTypedExt = value;
    //        }
    //    }

    //    public string COLUMN_TWO
    //    {
    //        get
    //        {
    //            try
    //            { 
    //                return this.objCOLUMN_TWO.DataValueTypedExt;
    //            }
    //            catch (System.Exception exp)
    //            {
    //                throw exp;
    //            }
    //        }
    //        set
    //        {
    //            this.objCOLUMN_TWO.DataValueTypedExt = value;
    //        }
    //    }

    //    public string COLUMN_THREE
    //    {
    //        get
    //        {
    //            try
    //            {
    //                return this.objCOLUMN_THREE.DataValueTypedExt;
    //            }
    //            catch (System.Exception exp)
    //            {
    //                throw exp;
    //            }
    //        }
    //        set
    //        {
    //            this.objCOLUMN_THREE.DataValueTypedExt = value;
    //        }
    //    }
    //}

    //class TempTableDataRowCollection : System.Collections.Generic.List<TempTableDataRow>
    //{}

    ////Following defines columns
}
