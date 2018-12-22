#pragma once
#include "math/Vector3D.h"
#include "math/Quaternion.h"
#include "math/Matrix4D.h"
#include <vector>
#include <memory>
using Math::Vector3D;
using Math::Quaternion;
using Math::Matrix4D;
namespace SRE {	
	class RenderObject;
	class Light;	
	class Sprite;
	class BillboardCollection;
	class ParticleSystem;
	class RayCaster;
	class TerrianTile;
	class Object3D {
	public:
		enum TransformSpace
		{
			LocalSpace,
			ParentSpace,
			WorldSpace
			
		};
		typedef std::shared_ptr<Object3D> ptr;
		typedef std::vector<Object3D::ptr> Children;
		Object3D() :_position(Vector3D(0.0, 0.0, 0.0)), _scale(Vector3D(1.0, 1.0, 1.0)) {_matrix_world = Matrix4D::makeIdentity();_parent = NULL;}
		Object3D(const Vector3D& pos) :_position(pos), _scale(Vector3D(1.0, 1.0, 1.0)) {_matrix_world = Matrix4D::makeIdentity();_parent = NULL;}
		Object3D(const Vector3D& pos, const Quaternion& quat) :_position(pos), _scale(Vector3D(1.0, 1.0, 1.0)), _orientation(quat) {_matrix_world = Matrix4D::makeIdentity();_parent = NULL;}
	public:
		virtual RenderObject* asRenderObject() { return NULL; }
		virtual const RenderObject* asRenderObject() const { return NULL; }

		virtual Light* asLight() { return NULL; }
		virtual const Light* asLight() const { return NULL; }

		virtual Sprite* asSprite() { return NULL; }
		virtual const Sprite* asSprite() const { return NULL; }

		virtual BillboardCollection* asBillboardCollection() { return NULL; }
		virtual const BillboardCollection* asBillboardCollection() const { return NULL; }

		virtual ParticleSystem* asParticleSystem() { return NULL; }
		virtual const ParticleSystem* asParticleSystem() const { return NULL; }

		virtual TerrianTile* asTerrianTile() { return NULL; }
		virtual const TerrianTile* asTerrianTile() const { return NULL; }

		virtual Object3D* asObject() { return this; }
		virtual const Object3D* asObject() const { return this; }

		virtual void raycast(RayCaster* raycaster) { }

	public:		
		//inline Object3D* getParent();
		inline Object3D* getParent() const { return _parent; }
		inline void setParent(Object3D* object) { _parent = object; }
		inline const Vector3D& getPosition()const { return _position; }
		inline void setPosition(const Vector3D& pos) { _position = pos; }
		inline const Vector3D& getScale()const { return _scale; }
		inline void setScale(const Vector3D& scale) { _scale = scale; }
		inline const Quaternion& getOrientation()const { return _orientation; }
		inline void setOrientation(const Quaternion& orientation) { _orientation = orientation; }

		void setDirection(const Vector3D& vec, TransformSpace space = LocalSpace, const Vector3D& localDirectionVector = Vector3D(0.0, 0.0, -1.0));

		void applyMatrix(const Matrix4D& matrix);
		//_orientation set
		void setRotationFromAxisAngle(const Vector3D& axis, double angle);
		void setRotationFromMatrix(const Matrix4D& rotate);
		//_orientation change
		void rotateOnAxis(const Vector3D& axis, double angle);
		void rotateOnAxisFixedPosition(const Vector3D& axis, double angle);//special use
		void rotateOnX(double angle) { rotateOnAxis(Vector3D(1.0, 0.0, 0.0), angle); }
		void rotateOnY(double angle) { rotateOnAxis(Vector3D(0.0, 1.0, 0.0), angle); }
		void rotateOnZ(double angle) { rotateOnAxis(Vector3D(0.0, 0.0, 1.0), angle); }
		void rotate(const Quaternion& quat, TransformSpace space = LocalSpace);
		//for position change
		void translateOnAxis(const Vector3D& axis, double distance);	
		void translateOnX(double distance) { translateOnAxis(Vector3D(1.0, 0.0, 0.0), distance); }
		void translateOnY(double distance) { translateOnAxis(Vector3D(0.0, 1.0, 0.0), distance); }
		void translateOnZ(double distance) { translateOnAxis(Vector3D(0.0, 0.0, 1.0), distance); }
		void translate(const Vector3D& vec, TransformSpace space = LocalSpace);

		void scale(const Vector3D& scale);
		void scale(double x, double y, double z);

		void updateFromParent();

		void roll(const float& angle, TransformSpace relativeSpace = LocalSpace);
		void pitch(const float& angle, TransformSpace relativeSpace = LocalSpace);
		void yaw(const float& angle, TransformSpace relativeSpace = LocalSpace);

		Vector3D getDirection()const { return _orientation * Vector3D(0, 0, 1); }
		Vector3D getUp(void) const { return _orientation * Vector3D(0, 1, 0); }
		Vector3D getRight(void) const { return _orientation * Vector3D(1, 0, 0); }

		//useful function
		void localToWorld(Vector3D& vector);
		void worldToLocal(Vector3D& vector);
		//
		bool add(Object3D* object);
		bool remove(Object3D* object);
		Object3D::ptr getChild(int index);	
		unsigned int getChildCount()const { return _children.size(); }
		
		//Children getChildren() { return _children; }
		void updateMatrixLocal();
		void updateMatrixWorld();
		//
		Matrix4D getLocalMatrix();
		Matrix4D getWorldMatrix();
		Vector3D getWorldPosition();
		Quaternion getWorldQuaternion();
		Vector3D getWorldScale();

	protected:
		bool _neadUpdate;
		bool _needUpdataParent;

		Object3D* _parent;
		Vector3D _position;
		Vector3D _scale;
		Quaternion _orientation;		
		Children _children;
		Matrix4D _matrix_local;
		Matrix4D _matrix_world;

		Vector3D _localPosition, _worldPosition;
		Vector3D _localScale, _worldScale;
		Quaternion _localOriention, _worldOriention;
		Matrix4D _localMatrix, _worldMatrix;

	};
}