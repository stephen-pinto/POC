//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;

#pragma warning disable 168
namespace DBTest.FinalStructure
{
    public class TempDataSet
    {
        public class TempTableDataTable : System.Data.TypedTableBase<TempTableDataRow>
        {
           
            public TempTableDataTable()
            {
                this.TableName = "TEMP_TABLE";
            }

            public int Count
            {
                get
                {
                    return this.Rows.Count;
                }
            }

            public TempTableDataRow this[int index]
            {
                get
                {
                    return this.Rows[index] as TempTableDataRow;
                }
            }

            public void AddTempTableRow(TempTableDataRow row)
            {
                this.Rows.Add(row);
            }

            protected TempTableDataTable(System.Runtime.Serialization.SerializationInfo info, System.Runtime.Serialization.StreamingContext context) :
                base(info, context)
            {}

            public TempTableDataRow AddTempTableRow(int COLUMN_ONE, string COLUMN_TWO, string COLUMN_THREE, float COLUMN_FOUR)
            {
                System.Data.DataRow DRow = this.NewRow();
                TempTableDataRow row = (TempTableDataRow)(DRow);
                object[] colValuesArray = new object[] 
                {
                    COLUMN_ONE,
                    COLUMN_TWO,
                    COLUMN_THREE,
                    COLUMN_FOUR
                };
                row.ItemArray = colValuesArray;
                this.Rows.Add(row);
                return row;
            }

            public TempTableDataRow NewTempTableRow()
            {
                return ((TempTableDataRow)this.NewRow());
            }

            protected override System.Data.DataRow NewRowFromBuilder(System.Data.DataRowBuilder builder)
            {
                return new TempTableDataRow(builder);
            }

            protected override System.Type GetRowType()
            {
                return typeof(TempTableDataRow);
            }

            public override System.Data.DataTable Clone()
            {
                TempTableDataTable cln = ((TempTableDataTable)base.Clone());
                return cln;
            }

            protected override System.Data.DataTable CreateInstance()
            {
                return new TempTableDataTable();
            } 
        }

        public class TempTableDataRow : System.Data.DataRow
        {
            public System.Data.DataColumn fieldCOLUMN_ONE = null;
            public System.Data.DataColumn fieldCOLUMN_TWO = null;
            public System.Data.DataColumn fieldCOLUMN_THREE = null;
            public System.Data.DataColumn fieldCOLUMN_FOUR = null;

            public void InitVars()
            {
                this.fieldCOLUMN_ONE = new System.Data.DataColumn("COLUMN_ONE", typeof(int), null, System.Data.MappingType.Element);
                if (!base.Table.Columns.Contains(fieldCOLUMN_ONE.ColumnName))
                    base.Table.Columns.Add(this.fieldCOLUMN_ONE);
                this.fieldCOLUMN_TWO = new System.Data.DataColumn("COLUMN_TWO", typeof(string), null, System.Data.MappingType.Element);
                if (!base.Table.Columns.Contains(fieldCOLUMN_TWO.ColumnName))
                    base.Table.Columns.Add(this.fieldCOLUMN_TWO);
                this.fieldCOLUMN_THREE = new System.Data.DataColumn("COLUMN_THREE", typeof(string), null, System.Data.MappingType.Element);
                if (!base.Table.Columns.Contains(fieldCOLUMN_THREE.ColumnName))
                    base.Table.Columns.Add(this.fieldCOLUMN_THREE);
                this.fieldCOLUMN_FOUR = new System.Data.DataColumn("COLUMN_FOUR", typeof(float), null, System.Data.MappingType.Element);
                if (!base.Table.Columns.Contains(fieldCOLUMN_FOUR.ColumnName))
                    base.Table.Columns.Add(this.fieldCOLUMN_FOUR);
                this.fieldCOLUMN_ONE.AllowDBNull = false;
                this.fieldCOLUMN_ONE.Unique = true;
                this.fieldCOLUMN_TWO.MaxLength = 20;
                this.fieldCOLUMN_THREE.MaxLength = 50;                
            }

            public TempTableDataRow(System.Data.DataRowBuilder builder) : base(builder)
            {
                InitVars();
            }

            public int COLUMN_ONE
            {
                get
                {
                    //A primary key field can never be null so we don't check for DBNull here.
                    return (int)(this[this.fieldCOLUMN_ONE]);
                }
                set
                {
                    this[this.fieldCOLUMN_ONE] = value;
                }
            }

            public string COLUMN_TWO
            {
                get
                {
                    try
                    {
                        return (string)(this[this.fieldCOLUMN_TWO]);
                    }
                    catch(global::System.InvalidCastException excptn)
                    {
                        return null;
                    }
                }
                set
                {
                    this[this.fieldCOLUMN_TWO] = value;
                }
            }

            public string COLUMN_THREE
            {
                get
                {
                    try
                    {
                        return (string)(this[this.fieldCOLUMN_THREE]);
                    }
                    catch(global::System.InvalidCastException excptn)
                    {
                        return null;
                    }
                }
                set
                {
                    this[this.fieldCOLUMN_THREE] = value;
                }
            }


            public float COLUMN_FOUR
            {
                get
                {
                    try
                    {
                        return (float)(this[this.fieldCOLUMN_FOUR]);
                    }
                    catch(global::System.InvalidCastException excptn)
                    {
                        return float.NegativeInfinity;                        
                    }
                }
                set
                {
                    this[this.fieldCOLUMN_FOUR] = value;
                }
            }

        }
    }
}
#pragma warning restore 168