#pragma once
// Copyright 2008, Microsoft Corporation and 2019 Alex Mytnyk
// Sample Code - Use restricted to terms of use defined in the accompanying license agreement (EULA.doc)
//--------------------------------------------------------------
#include <iostream>
#include <string>
#include <ctime>
#include "Serializers.hpp"
#include <optional>
namespace Materialise {
	const std::string schema_generated_files_PreprocessorCapabilities_namespace = "http://www.materialise.com/BuildProcessor/2014";
	struct PreprocessorCapabilities;
	struct PreprocessorCapabilities {
		void Write(IXmlSerializerWriter& s, const std::string& __name__);
		bool Read(IXmlSerializerReader& s, const std::string& __name__);
		PreprocessorCapabilities(const PreprocessorCapabilities&) = delete;
		PreprocessorCapabilities& operator=(PreprocessorCapabilities&&) = delete;
		PreprocessorCapabilities& operator=(PreprocessorCapabilities&) = delete;
		PreprocessorCapabilities(PreprocessorCapabilities&&) noexcept;
		PreprocessorCapabilities() = default;
		~PreprocessorCapabilities() = default;
		std::optional<bool> Labelling {false};
		std::optional<bool> DeferredLabelling {false};
	};
}
Materialise::PreprocessorCapabilities::PreprocessorCapabilities(Materialise::PreprocessorCapabilities &&___PreprocessorCapabilities) noexcept
	: Labelling(___PreprocessorCapabilities.Labelling)
	, DeferredLabelling(___PreprocessorCapabilities.DeferredLabelling)
{ }
void Materialise::PreprocessorCapabilities::Write(IXmlSerializerWriter& s, const std::string& __name__) {
	IXmlSerializerWriter::Scope scope(s, __name__);
	if (Labelling.has_value())
		s.Write("Labelling", Labelling.value());
	if (DeferredLabelling.has_value())
		s.Write("DeferredLabelling", DeferredLabelling.value());
}
bool Materialise::PreprocessorCapabilities::Read(IXmlSerializerReader& s, const std::string& __name__) {
	IXmlSerializerReader::Scope scope(s, __name__);
	if (!scope.exist())
		return false;
	bool __Labelling;
	if (s.ReadBool("Labelling", __Labelling))
		Labelling = std::make_optional(__Labelling);
	bool __DeferredLabelling;
	if (s.ReadBool("DeferredLabelling", __DeferredLabelling))
		DeferredLabelling = std::make_optional(__DeferredLabelling);
	return true;
}
