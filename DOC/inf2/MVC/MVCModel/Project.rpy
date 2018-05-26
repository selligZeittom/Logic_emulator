I-Logix-RPY-Archive version 8.6.0 C++ 2071424
{ IProject 
	- _id = GUID cbfea505-2e4a-4683-99ec-6c89f95b22c6;
	- _myState = 8192;
	- _properties = { IPropertyContainer 
		- Subjects = { IRPYRawContainer 
			- size = 2;
			- value = 
			{ IPropertySubject 
				- _Name = "Format";
				- Metaclasses = { IRPYRawContainer 
					- size = 2;
					- value = 
					{ IPropertyMetaclass 
						- _Name = "Association";
						- Properties = { IRPYRawContainer 
							- size = 4;
							- value = 
							{ IProperty 
								- _Name = "Font.Font";
								- _Value = "Tahoma";
								- _Type = String;
							}
							{ IProperty 
								- _Name = "Font.Size";
								- _Value = "8";
								- _Type = Int;
							}
							{ IProperty 
								- _Name = "Line.LineColor";
								- _Value = "128,128,128";
								- _Type = Color;
							}
							{ IProperty 
								- _Name = "Line.LineWidth";
								- _Value = "1";
								- _Type = Int;
							}
						}
					}
					{ IPropertyMetaclass 
						- _Name = "Composition";
						- Properties = { IRPYRawContainer 
							- size = 4;
							- value = 
							{ IProperty 
								- _Name = "Font.Font";
								- _Value = "Tahoma";
								- _Type = String;
							}
							{ IProperty 
								- _Name = "Font.Size";
								- _Value = "8";
								- _Type = Int;
							}
							{ IProperty 
								- _Name = "Line.LineColor";
								- _Value = "128,128,128";
								- _Type = Color;
							}
							{ IProperty 
								- _Name = "Line.LineWidth";
								- _Value = "1";
								- _Type = Int;
							}
						}
					}
				}
			}
			{ IPropertySubject 
				- _Name = "ObjectModelGe";
				- Metaclasses = { IRPYRawContainer 
					- size = 2;
					- value = 
					{ IPropertyMetaclass 
						- _Name = "Association";
						- Properties = { IRPYRawContainer 
							- size = 9;
							- value = 
							{ IProperty 
								- _Name = "ShowName";
								- _Value = "Name";
								- _Type = Enum;
								- _ExtraTypeInfo = "Name,Label,None";
							}
							{ IProperty 
								- _Name = "ShowSourceMultiplicity";
								- _Value = "True";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "ShowSourceQualifier";
								- _Value = "True";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "ShowSourceRole";
								- _Value = "False";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "ShowStereotype";
								- _Value = "None";
								- _Type = Enum;
								- _ExtraTypeInfo = "Label,Bitmap,None";
							}
							{ IProperty 
								- _Name = "ShowTargetMultiplicity";
								- _Value = "True";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "ShowTargetQualifier";
								- _Value = "True";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "ShowTargetRole";
								- _Value = "True";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "line_style";
								- _Value = "rectilinear_arrows";
								- _Type = Enum;
								- _ExtraTypeInfo = "straight_arrows,rectilinear_arrows,spline_arrows";
							}
						}
					}
					{ IPropertyMetaclass 
						- _Name = "Composition";
						- Properties = { IRPYRawContainer 
							- size = 9;
							- value = 
							{ IProperty 
								- _Name = "ShowName";
								- _Value = "Name";
								- _Type = Enum;
								- _ExtraTypeInfo = "Name,Label,None";
							}
							{ IProperty 
								- _Name = "ShowSourceMultiplicity";
								- _Value = "True";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "ShowSourceQualifier";
								- _Value = "True";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "ShowSourceRole";
								- _Value = "False";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "ShowStereotype";
								- _Value = "None";
								- _Type = Enum;
								- _ExtraTypeInfo = "Label,Bitmap,None";
							}
							{ IProperty 
								- _Name = "ShowTargetMultiplicity";
								- _Value = "True";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "ShowTargetQualifier";
								- _Value = "True";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "ShowTargetRole";
								- _Value = "True";
								- _Type = Bool;
							}
							{ IProperty 
								- _Name = "line_style";
								- _Value = "rectilinear_arrows";
								- _Type = Enum;
								- _ExtraTypeInfo = "straight_arrows,rectilinear_arrows,spline_arrows";
							}
						}
					}
				}
			}
		}
	}
	- _name = "Project";
	- _UserColors = { IRPYRawContainer 
		- size = 16;
		- value = 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 
	}
	- _defaultSubsystem = { ISubsystemHandle 
		- _m2Class = "ISubsystem";
		- _filename = "MVCSample.sbs";
		- _subsystem = "";
		- _class = "";
		- _name = "MVCSample";
		- _id = GUID 1a15992e-4270-427c-8559-dfb648d40470;
	}
	- _component = { IHandle 
		- _m2Class = "IComponent";
		- _filename = "DefaultComponent.cmp";
		- _subsystem = "";
		- _class = "";
		- _name = "DefaultComponent";
		- _id = GUID c29d1002-93dc-44a7-87d5-66a87a8c9fdf;
	}
	- Multiplicities = { IRPYRawContainer 
		- size = 4;
		- value = 
		{ IMultiplicityItem 
			- _name = "1";
			- _count = -1;
		}
		{ IMultiplicityItem 
			- _name = "*";
			- _count = -1;
		}
		{ IMultiplicityItem 
			- _name = "0,1";
			- _count = -1;
		}
		{ IMultiplicityItem 
			- _name = "1..*";
			- _count = -1;
		}
	}
	- Subsystems = { IRPYRawContainer 
		- size = 1;
		- value = 
		{ ISubsystem 
			- fileName = "MVCSample";
			- _id = GUID 1a15992e-4270-427c-8559-dfb648d40470;
		}
	}
	- Diagrams = { IRPYRawContainer 
		- size = 1;
		- value = 
		{ IDiagram 
			- _id = GUID 0de7fda7-e9a7-4030-bcd8-e89643c9cb9b;
			- _myState = 8192;
			- _properties = { IPropertyContainer 
				- Subjects = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertySubject 
						- _Name = "Format";
						- Metaclasses = { IRPYRawContainer 
							- size = 2;
							- value = 
							{ IPropertyMetaclass 
								- _Name = "Association";
								- Properties = { IRPYRawContainer 
									- size = 4;
									- value = 
									{ IProperty 
										- _Name = "Font.Font";
										- _Value = "Tahoma";
										- _Type = String;
									}
									{ IProperty 
										- _Name = "Font.Size";
										- _Value = "8";
										- _Type = Int;
									}
									{ IProperty 
										- _Name = "Line.LineColor";
										- _Value = "128,128,128";
										- _Type = Color;
									}
									{ IProperty 
										- _Name = "Line.LineWidth";
										- _Value = "1";
										- _Type = Int;
									}
								}
							}
							{ IPropertyMetaclass 
								- _Name = "Composition";
								- Properties = { IRPYRawContainer 
									- size = 4;
									- value = 
									{ IProperty 
										- _Name = "Font.Font";
										- _Value = "Tahoma";
										- _Type = String;
									}
									{ IProperty 
										- _Name = "Font.Size";
										- _Value = "8";
										- _Type = Int;
									}
									{ IProperty 
										- _Name = "Line.LineColor";
										- _Value = "128,128,128";
										- _Type = Color;
									}
									{ IProperty 
										- _Name = "Line.LineWidth";
										- _Value = "1";
										- _Type = Int;
									}
								}
							}
						}
					}
				}
			}
			- _name = "Model1";
			- _lastModifiedTime = "5.2.2016::8:18:22";
			- _graphicChart = { CGIClassChart 
				- _id = GUID a59838e2-5ef3-4a3e-bcb7-37f21eef2553;
				- m_type = 0;
				- m_pModelObject = { IHandle 
					- _m2Class = "IDiagram";
					- _id = GUID 0de7fda7-e9a7-4030-bcd8-e89643c9cb9b;
				}
				- m_pParent = ;
				- m_name = { CGIText 
					- m_str = "";
					- m_style = "Arial" 10 0 0 0 1 ;
					- m_color = { IColor 
						- m_fgColor = 0;
						- m_bgColor = 0;
						- m_bgFlag = 0;
					}
					- m_position = 1 0 0  ;
					- m_nIdent = 0;
					- m_bImplicitSetRectPoints = 0;
					- m_nOrientationCtrlPt = 8;
				}
				- m_drawBehavior = 0;
				- m_bIsPreferencesInitialized = 0;
				- elementList = 1;
				{ CGIClass 
					- _id = GUID fbd0c41d-02fb-4d25-89cc-a9bee27ccdf4;
					- m_type = 78;
					- m_pModelObject = { IHandle 
						- _m2Class = "IClass";
						- _filename = "MVCSample.sbs";
						- _subsystem = "MVCSample";
						- _class = "";
						- _name = "TopLevel";
						- _id = GUID 60d9e630-aab2-4633-9f54-ed8f66f0815f;
					}
					- m_pParent = ;
					- m_name = { CGIText 
						- m_str = "TopLevel";
						- m_style = "Arial" 10 0 0 0 1 ;
						- m_color = { IColor 
							- m_fgColor = 0;
							- m_bgColor = 0;
							- m_bgFlag = 0;
						}
						- m_position = 1 0 0  ;
						- m_nIdent = 0;
						- m_bImplicitSetRectPoints = 0;
						- m_nOrientationCtrlPt = 5;
					}
					- m_drawBehavior = 0;
					- m_bIsPreferencesInitialized = 0;
					- m_AdditionalLabel = { CGIText 
						- m_str = "";
						- m_style = "Arial" 10 0 0 0 1 ;
						- m_color = { IColor 
							- m_fgColor = 0;
							- m_bgColor = 0;
							- m_bgFlag = 0;
						}
						- m_position = 1 0 0  ;
						- m_nIdent = 0;
						- m_bImplicitSetRectPoints = 0;
						- m_nOrientationCtrlPt = 1;
					}
					- m_polygon = 0 ;
					- m_nNameFormat = 0;
					- m_nIsNameFormat = 0;
					- Compartments = { IRPYRawContainer 
						- size = 0;
					}
					- Attrs = { IRPYRawContainer 
						- size = 0;
					}
					- Operations = { IRPYRawContainer 
						- size = 0;
					}
				}
				
				- m_access = 'Z';
				- m_modified = 'N';
				- m_fileVersion = "";
				- m_nModifyDate = 0;
				- m_nCreateDate = 0;
				- m_creator = "";
				- m_bScaleWithZoom = 1;
				- m_arrowStyle = 'S';
				- m_pRoot = GUID fbd0c41d-02fb-4d25-89cc-a9bee27ccdf4;
				- m_currentLeftTop = 0 0 ;
				- m_currentRightBottom = 0 0 ;
			}
			- _defaultSubsystem = { IHandle 
				- _m2Class = "ISubsystem";
				- _filename = "MVCSample.sbs";
				- _subsystem = "";
				- _class = "";
				- _name = "MVCSample";
				- _id = GUID 1a15992e-4270-427c-8559-dfb648d40470;
			}
		}
	}
	- Components = { IRPYRawContainer 
		- size = 1;
		- value = 
		{ IComponent 
			- fileName = "DefaultComponent";
			- _id = GUID c29d1002-93dc-44a7-87d5-66a87a8c9fdf;
		}
	}
}

