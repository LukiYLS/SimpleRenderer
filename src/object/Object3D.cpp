#include "Object3D.h"
#include "math/Vector4D.h"
#include <iostream>
namespace SRE {


	void Object3D::applyMatrix(const Matrix4D& matrix)
	{
		_matrix_local = _matrix_local * matrix;
		_matrix_local.decompose(_position, _scale, _orientation);
	}
	void Object3D::setRotationFromAxisAngle(const Vector3D& axis, double angle)
	{
		_orientation.setFromAxisAngle(angle, axis);
	}
	void Object3D::setRotationFromMatrix(const Matrix4D& rotate)
	{
		_orientation.setFromRotationMatrix(rotate);
	}
	void Object3D::rotateOnAxis(const Vector3D& axis, double angle)
	{
		Quaternion quat;
		quat.setFromAxisAngle(angle, axis);
		_orientation = _orientation * quat;
		//_position = _position * quat;//
	}
	void Object3D::setDirection(const Vector3D& vec, TransformSpace space /* = LocalSpace */, const Vector3D& localDirectionVector /* = Vector3D(0.0, 0.0, -1.0) */)
	{
		Vector3D targetDir = vec;
		targetDir.normalize();

		switch (space)
		{
		case LocalSpace:
			if (_parent)
			{
				targetDir = _parent->getOrientation() * targetDir;
			}
			break;
		case ParentSpace:
			targetDir = _orientation * targetDir;
			break;
		case WorldSpace: 
			//_orientation = _orientation * _orientation().Inverse()
			//	* quat * _getDerivedOrientation();
			break;
		}
		Quaternion targetOrientation;
		const Quaternion& currentOrientation = getOrientation();
		Vector3D currentDir = currentOrientation * localDirectionVector;

		if ((currentDir + targetDir).squaredLength() < 0.00005f)
		{
			// Oops, a 180 degree turn (infinite possible rotation axes)
			// Default to yaw i.e. use current UP
			targetOrientation =
				Quaternion(-currentOrientation.y, -currentOrientation.z, currentOrientation.w, currentOrientation.x);
		}
		else
		{		
			Quaternion rotQuat = currentDir.getRotationTo(targetDir);
			targetOrientation = rotQuat * currentOrientation;
		}
		if (_parent)
			setOrientation(_parent->getWorldQuaternion().getUnitInverse() * targetOrientation);
		else
			setOrientation(targetOrientation);
	}
	void Object3D::rotate(const Quaternion& quat, TransformSpace space)
	{
		switch (space)
		{
		case LocalSpace:
			_orientation = _orientation * quat;
			break;
		case ParentSpace:
			_orientation = quat * _orientation;
			break;
		case WorldSpace:
			//_orientation = _orientation * _orientation().Inverse()
			//	* quat * _getDerivedOrientation();
			break;
		}
		_orientation.normalize();
		_neadUpdate = true;
	}
	void Object3D::rotateOnAxisFixedPosition(const Vector3D& axis, double angle)
	{
		Quaternion quat;
		quat.setFromAxisAngle(angle, axis);
		_orientation = _orientation * quat;
		_position = _position * quat;//
	}
	void Object3D::translateOnAxis(const Vector3D& axis, double distance)
	{

		Vector3D new_axis = axis * _orientation;//�õ���ת�������
		_position += (distance * new_axis);		
	}
	void Object3D::translate(const Vector3D& vec, TransformSpace space)
	{
		switch (space)
		{
		case LocalSpace:
			_position += _orientation * vec;
			break;
		case ParentSpace:
			_position += vec;
			break;
		case WorldSpace:
			//_orientation = _orientation * _orientation().Inverse()
			//	* quat * _getDerivedOrientation();
			break;
		}
		_neadUpdate = true;
	}
	void Object3D::scale(const Vector3D& scale)
	{
		_scale = scale * _scale;		
		_neadUpdate = true;
	}

	void Object3D::scale(double x, double y, double z)
	{
		_scale.x *= x;
		_scale.y *= y;
		_scale.z *= z;		
		_neadUpdate = true;
	}
	void Object3D::updateFromParent()
	{
		if (_parent)
		{
			//�жϸýڵ��Ƿ���������ڵ�
			const Quaternion parentOrientation = _parent->getWorldQuaternion();
			_worldOriention = parentOrientation * _localOriention;

			const Vector3D parentScale = _parent->getWorldScale();
			_worldScale = parentScale * _localScale;

			_worldPosition = parentOrientation * (parentScale * _localPosition);
			_worldPosition += _parent->getWorldPosition();

		}
		else
		{
			_worldOriention = _localOriention;
			_worldScale = _localScale;
			_worldPosition = _localPosition;
		}
		_needUpdataParent = false;
	}
	//---------------
	void Object3D::localToWorld(Vector3D& vector)
	{
		vector = _matrix_world * vector;
	}
	void Object3D::worldToLocal(Vector3D& vector)
	{
		Matrix4D matrix_inverse = _matrix_world.getInverse();
		vector = matrix_inverse * vector;
	}
	bool Object3D::add(Object3D* object)
	{
		
		if (!object)return false;
		// Object3D* parent = object->getParent();
		// if (parent)
		// 	parent->remove(object);
		 object->setParent(this);
		_children.push_back((Object3D::ptr)object);
		return true;
	}
	bool Object3D::remove(Object3D* object)
	{
		for (Children::iterator it = _children.begin();it!=_children.end();it++)
		{
			if (it->get() == object)
			{
				_children.erase(it);
				return true;
			}
				
		}
		return false;
	}
	Object3D::ptr Object3D::getChild(int index)
	{
		if (index < _children.size())
			return _children[index];
		return NULL;
	}
	void Object3D::updateMatrixLocal()
	{
		_matrix_local = Matrix4D::makeTransformMatrix(_position, _scale, _orientation);
	}
	void Object3D::updateMatrixWorld()
	{
		this->updateMatrixLocal();
		if (this->getParent() == NULL)
			_matrix_world = _matrix_local;
		else
		{
			_matrix_world = _matrix_local * this->getParent()->getWorldMatrix();
		}
		if (_children.size() == 0)return;
		for (auto child : _children)
			child->updateMatrixWorld();
	}

	Matrix4D Object3D::getLocalMatrix()
	{		
		return _matrix_local;
	}

	Matrix4D Object3D::getWorldMatrix()
	{		
		return _matrix_world;
	}

	Vector3D Object3D::getWorldPosition()
	{
		this->updateMatrixWorld();
		//this->_matrix_world.decompose(_position, _scale, _orientation);
		return Vector3D(_matrix_world[12], _matrix_world[13], _matrix_world[14]);
	}

	Quaternion Object3D::getWorldQuaternion()
	{
		this->updateMatrixWorld();
		this->_matrix_world.decompose(_position, _scale, _orientation);
		return _orientation;
	}

	Vector3D Object3D::getWorldScale()
	{
		this->updateMatrixWorld();
		this->_matrix_world.decompose(_position, _scale, _orientation);
		return _scale;
	}

}