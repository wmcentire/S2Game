#pragma once
#include "Serialization/Serializable.h"
#include "Vector2.h"
#include "Matrix2x2.h"

namespace pb {

	struct Transform : public ISerializable {
		Vector2 position;
		float rotation{ 0 };
		Vector2 scale{ 1, 1 };

		Transform() = default;
		Transform(const Vector2& position, float rotation, const Vector2& scale) : 
			position{position},
			rotation{rotation},
			scale{scale} {}

		// Inherited via ISerializable
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
		/*
		operator Matrix2x2 () const {
			Matrix2x2 mxScale = Matrix2x2::CreateScale(scale);
			//Matrix2x2 mxRotation = Matrix2x2::CreateRotation(pb::DegToRad(rotation));

			return { mxScale * mxRotation };
		}*/
	};


}