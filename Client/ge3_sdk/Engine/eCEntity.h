#ifndef _ECENTITY_H
#define _ECENTITY_H
class eCEntityPropertySet;
enum eEPropertySetType;
struct eSEntityFlags
{
    unsigned int m_Locked            : 1;  // 00000001 0
    unsigned int m_RenderingEnabled  : 1;  // 00000002 1
    unsigned int m_Enabled           : 1;  // 00000004 2
    unsigned int m_Killed            : 1;  // 00000008 3
    unsigned int m_InProcessingRange : 1;  // 00000010 4
    unsigned int m_CachedIn          : 1;  // 00000020 5
    unsigned int m_EventsEnabled     : 1;  // 00000040 6
    unsigned int m_PickingEnabled    : 1;  // 00000080 7
    unsigned int m_CollisionEnabled  : 1;  // 00000100 8
    unsigned int __FIXME_9           : 1;  // 00000200 9
    unsigned int m_InsertType        : 4;  // 00003C00 10..13 // eCEntity::eEInsertType
    unsigned int __FIXME_14          : 1;  // 00004000 14
    unsigned int __FIXME_15          : 1;  // 00008000 15
    unsigned int __FIXME_16          : 1;  // 00010000 16
    unsigned int m_IsDynamic         : 1;  // 00020000 17
    unsigned int __FIXME_18          : 1;  // 00040000 18
    unsigned int m_IsSaveGameRelevant: 1;  // 00080000 19
    unsigned int m_IsTemporary       : 1;  // 00100000 20
    unsigned int m_IsFrozen          : 1;  // 00200000 21
    unsigned int m_IsBurned          : 1;  // 00400000 22
    unsigned int m_IsHighlighted     : 1;  // 00800000 23
    unsigned int __FIXME             : 8;  // FF000000 24..31
};

#pragma warning( push )
#pragma warning( disable : 4251 )
class DLLIMPORT eCEntity
	: public eCNode
{
public:
	enum eEInsertType
	{
		eEInsertType_None,
        eEInsertType_Floor,
        eEInsertType_Ground,
        eEInsertType_Tree,
        eEInsertType_Wall,
        eEInsertType_Arrow,
        eEInsertType_Manual,
        eEInsertType_ForceDWORD = FORCE_DWORD
	};

	virtual bCPropertyID & GetID( void );
	virtual eCEntityPropertySet* GetPropertySet( eEPropertySetType );
	eCEntityPropertySet* GetPropertySet( const bCString & ); //dynamic_cast to your value
	//bool CreateFromTemplate( const eCTemplateEntity & );
	bool CreateFromTemplate( const bCPropertyID & );
	bool CreateFromTemplate( const bCString & );
	virtual void Kill( void );
	virtual void Destroy( void );
	//eInsertType GetInsertType( void );
	//void SetInsertType( eInsertType );
	void SetTemporary( void );
	bool IsEnabled( void ) const;
	void Enable( bool );
	void EnableRendering( bool );
	bool IsLocked( void ) const;
	void Lock( bool );
	bool IsProcessingDisabled( void ) const;
	void DisableProcessing( bool );
	bool HasCollision( void ) const;
	void EnableCollision( bool );
	virtual void SetName( const bCString & );
	virtual void SetLocalPosition( const bCVector & );
	virtual void SetWorldPosition( const bCVector& );
	void GetLocalPosition( bCVector & ) const;
	void GetWorldPosition( bCVector & ) const;
	void MoveToLocalNode( eCEntity * );
	void MoveToWorldNode( eCEntity * );
	float GetDistanceToEntity( const eCEntity & );
	void SetMotionDelta(const bCVector &);
	void SetWorldMatrix(const bCMatrix *);
	
	eCEntity( void );
	eCEntity( const eCEntity & );
	~eCEntity( void );
	
	void RenderName( float );
	bCQuaternion GetLocalRotation( void ) const;
	void SetLocalRotation( const bCQuaternion & );
	const bCMatrix* GetWorldMatrix( void );
	bCQuaternion GetWorldRotation( void ) const;
	void GetLocalRotation( bCQuaternion& );
	const bCString & GetName( void ) const;
	
};
#pragma warning( pop )
#endif