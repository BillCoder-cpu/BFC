//*/
/*
					Script_C.h : 
	
		This source file is part of the BFC Engine.
		
	Author: William P. Foster (bill@software0imagination.com)

// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2026 William P. Foster
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

//*/


namespace CBfcScript
{
	
	BFC_CLASS ParseIncludes
	{
		public:
			ParseIncludes	();
			ParseIncludes	(const CBfc::STRING &includePath, const CBfc::STRING &csSkipIncludes);
			int	LocateFile(const CBfc::Filename &fn, CBfc::Filename &out_fullPath, const CBfc::Filename &curdir);
		private:
			Phrase	m_phrase_includePath;
			Phrase	m_phSkipIncludes;
	};

	BFC_CLASS C_Define
	{
		public:
			C_Define (const CBfc::STRING &tag, const CBfc::STRING &value, const CBfc::STRING& original_value)
			{
				m_cs_defname=tag;
				m_cs_substitute=value;
				m_cs_original_substitute = original_value;
			}
			void SetArgumentString(const CBfc::STRING &cs_args)
			{
				m_cs_args = cs_args;
			}
		CBfc::STRING		m_cs_defname;
		CBfc::STRING		m_cs_substitute;
		CBfc::STRING		m_cs_args;
		CBfc::STRING		m_cs_original_substitute;
	};

BFC_CLASS Script_C : public Script_Source
{
	public:
		Script_C (CBfc::Stream &bfc_stream,const CBfc::STRING &csIncludePaths, const CBfc::STRING &csSkipIncludes, const CBfc::STRING &csDefines, const bool bSkipAllIncludes)
			: Script_Source(bfc_stream)
				, m_pi (csIncludePaths,csSkipIncludes), m_bSkipAllIncludes(bSkipAllIncludes)
				, m_ifdef_depth(0), m_ifdef_on_depth(0)
				{
					construct();
					AddDefines(csDefines);
				}
		Script_C (CBfc::Stream &bfc_stream)
			: Script_Source(bfc_stream)
				, m_bSkipAllIncludes(false)
				, m_ifdef_depth(0), m_ifdef_on_depth(0)
				{
					construct();
				}

		typedef enum {
			E_IFDEF_IF,
			E_IFDEF_IFDEF,
			E_IFDEF_IFNDEF,
			E_IFDEF_ELSE,
			E_IFDEF_ENDIF
		} E_C_IFDEF;

		
			// read a until next dealio
			// returns deliminator in finalc
		bool ReadSourceLine (CBfc::STRING &s, character &finalc);		
		bool ReadBetweenBrackets(CBfc::STRING &s);
		
		bool PopSource ();
		
		bool LocateDefine(const STRING &tag, UINT &index);
		CBfc::Array<C_Define>				m_defines;
protected:
		virtual bool	BufferNextLine ();

		void	AddDefine (const STRING& tag, const STRING& value, const STRING& argl, const STRING& original_value);
		void	SubstituteDefines();;
		
		bool ReadAheadScript_Character_NoDefines(character &c);
		bool ProcessDirective();
		bool ReadDefineDirective();
		bool ReadUndefDirective();
		bool ReadIfdefDirective(E_C_IFDEF eif);

		bool ScanIncludefile();
		
		bool skipping_code() const {
			return (m_ifdef_on_depth != m_ifdef_depth);
		}


		bool WithinInclude () const { return !m_StreamStack.IsEmpty(); }
		
		ParseIncludes			m_pi;				// include Path
		
private:
	bool ReadIfdefDirective_internal(const E_C_IFDEF eif);
	bool PushSource(const CBfc::Filename &fn);
	void PushSource(CBfc::StreamSource *p_stream);
	void DetectWorkingFolder();

private:
	bool 	m_bSkipAllIncludes;
		
		void construct()
		{
			STRING	*p_s_cc = new STRING("//");	  // midline comment indicator for C language
			
			m_saMidlineCommentChars.Empty();
			m_saMidlineCommentChars.Add (p_s_cc);
			DetectWorkingFolder();
		}

		void AddDefines(const CBfc::STRING &csDefines);
			
protected:
	CBfc::STRING						m_cs_pwdWorkingFrom;
	CBfc::STRING						m_cs_LastComment;		// Store each comment here.
	
 	UINT								m_ifdef_depth;
	UINT								m_ifdef_on_depth;	// level at which good code resides
	
	CBfc::StringArray					m_csa_scannedincludes;
	
	CBfc::Array<CBfc::StreamSource*>	m_StreamStack;
	CBfc::Array<UINT>					m_LinenumberStack;
};

}
